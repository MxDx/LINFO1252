                if (space_in_front > 0) {
                    MY_HEAP[i + 3 + size] = 0;
                    MY_HEAP[i + 4 + size] = space_in_front >> 8;
                    MY_HEAP[i + 5 + size] = space_in_front & 0x00FF;
                }