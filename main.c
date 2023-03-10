#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

// 난수 생성 함수
void randomNumber(struct Sort *sort)
{
    for (int i = sort->startIndex; i < sort->length; ++i)
        sort->arr[i] = rand() % 101;
}

int main(void)
{

    srand((unsigned)time(NULL));     // srand 초기화
    struct Sort *sort = sort_init(); // sort 클래스(구조체) 생성 및 인스턴스화 (초기화)

    printf("***********************************\n");
    printf("*** 여러가지 정렬 프로그램 구현  ***\n");
    printf("***                             ***\n");
    printf("*** 1. 선택(selection) 정렬     ***\n");
    printf("*** 2. 삽입(insertion) 정렬     ***\n");
    printf("*** 3. 버블(bubble) 정렬        ***\n");
    printf("*** 4. 퀵(quick) 정렬           ***\n");
    printf("*** 5. 합병(merge) 정렬         ***\n");
    printf("*** 6. 힙(heap) 정렬            ***\n");
    printf("*** 7. 종료(quit) 정렬          ***\n");
    printf("***********************************\n");

    int ticket;
    while (1)
    {

        randomNumber(sort);
        printf("번호 입력 : ");
        scanf(" %d", &ticket); // ticket 입력

        switch (ticket)
        {
        case 1:
            printf("<선택정렬>\n");
            printf("정렬 전 : ");
            sort->print(sort);
            printf("\n");
            sort->selectSort(sort); // selectSort 함수 호출
            printf("정렬 후 : ");
            sort->print(sort);
            break;

        case 2:
            printf("<삽입정렬>\n");
            printf("정렬 전 : ");
            sort->print(sort);
            printf("\n");
            sort->insertSort(sort); // insertSort 함수 호출
            printf("정렬 후 : ");
            sort->print(sort);
            break;

        case 3:
            printf("<거품정렬>\n");
            printf("정렬 전 : ");
            sort->print(sort);
            printf("\n");
            sort->bubbleSort(sort); // bubbleSort 함수 호출
            printf("정렬 후 : ");
            sort->print(sort);
            break;

        case 4:
            printf("<빠른정렬>\n");
            printf("정렬 전 : ");
            sort->print(sort);
            printf("\n");
            sort->quickSort(sort); // quickSort 함수 호출
            printf("정렬 후 : ");
            sort->print(sort);
            break;

        case 5:
            printf("<합병정렬>\n");
            printf("정렬 전 : ");
            sort->print(sort);
            printf("\n");
            sort->mergeSort(sort); // mergeSort 함수 호출
            printf("정렬 후 : ");
            sort->print(sort);
            break;

        case 6:
            printf("<힙정렬>\n");
            printf("정렬 전 : ");
            sort->print(sort);
            printf("\n");
            sort->heapSort(sort); // heapSort 함수 호출
            printf("정렬 후 : ");
            sort->print(sort);
            break;

        case 7:
            printf("<종료>");
            return 0;

        default:
            printf("<번호오류>");
        }
        puts("\n");
    }
}
