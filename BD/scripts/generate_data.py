#!/usr/bin/env python3
from dataclasses import dataclass
import random

@dataclass
class Data:
    id_: int

    def __init__(self):
        self.id_ = random.randint(100000000, 99999999999999)


def main():
    N = int(input('N: '))
    for _ in range(N):
        print(Data().id_)


if __name__ == '__main__':
    main()
