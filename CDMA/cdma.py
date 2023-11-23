import multiprocessing

# 송신기 프로세스


def transmitter(conn, chip_seq, bit):
    # 비트와 칩 시퀀스를 곱하여 전송 신호를 계산
    signal = [int(bit) * x for x in chip_seq]
    # 전송 신호를 조이너 프로세스에 전송
    conn.send(signal)
    conn.close()

# 수신기 프로세스


def receiver(conn, chip_seq):
    # 조이너 프로세스로부터 결합된 신호를 받음
    combined_signal = conn.recv()
    # 결합된 신호와 칩 시퀀스의 내적을 계산하여 전송된 비트를 알아냄
    result = sum(x*y for x, y in zip(combined_signal, chip_seq))
    # 결과의 부호에 따라 비트를 결정
    bit = 1 if result > 0 else 0
    print(f"받은 비트: {bit}")
    conn.close()


def main():
    # 표준 입력으로부터 4개의 칩 시퀀스와 4개의 비트 시퀀스를 읽어옴
    chip_sequences = []
    for i in range(4):
        print(f"스테이션 {i}의 칩 시퀀스를 입력하세요 (예: -1 1 -1 1 -1 1 -1 1):")
        chip_sequence = list(map(int, input().split()))
        chip_sequences.append(chip_sequence)

    print("송신기마다 한 비트씩 4개의 비트 시퀀스를 입력하세요:")
    bits = list(map(int, input().split()))

    # 통신을 위한 파이프를 설정
    tx_pipes = [multiprocessing.Pipe() for _ in range(4)]
    rx_pipes = [multiprocessing.Pipe() for _ in range(4)]

    # 송신기와 수신기 프로세스를 생성
    tx_processes = []
    rx_processes = []

    for i in range(4):
        tx_process = multiprocessing.Process(target=transmitter, args=(
            tx_pipes[i][1], chip_sequences[i], bits[i]))
        rx_process = multiprocessing.Process(
            target=receiver, args=(rx_pipes[i][0], chip_sequences[i]))
        tx_processes.append(tx_process)
        rx_processes.append(rx_process)
        tx_process.start()
        rx_process.start()

    # 조이너 프로세스
    combined_signal = [0] * 8
    for tx_pipe in tx_pipes:
        signal = tx_pipe[0].recv()
        combined_signal = [x + y for x, y in zip(combined_signal, signal)]

    for rx_pipe in rx_pipes:
        rx_pipe[1].send(combined_signal)

    # 모든 프로세스가 완료될 때까지 기다림
    for process in tx_processes + rx_processes:
        process.join()


if __name__ == '__main__':
    main()
