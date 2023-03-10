/* 코드 읽기 전 필독
 * C언어의 함수 포인터를 이용해서 객체처럼 코드를 작성했습니다.
 * 그러므로 객체 지향적인 개념을 사용할 것이므로 유의해 주시기 바랍니다.
 */

#define SWAP(X, Y)    \
    {                 \
        int TEMP = X; \
        X = Y;        \
        Y = TEMP;     \
    }
#define MAX_SIZE 100 // MAX_SIZE : 100
#define SIZE 25      // SIZE : 25

struct Sort
{ // Sort 클래스 작성 부분

    // 함수[메소드] (기능) : 함수 포인터 선언
    void (*selectSort)(struct Sort *sort);  // 선택 정렬 함수 포인터
    void (*insertSort)(struct Sort *sort);  // 삽입 정렬 함수 포인터
    void (*bubbleSort)(struct Sort *sort);  // 거품 정렬 함수 포인터
    void (*quickSort)(struct Sort *sort);   // 빠른 정렬 함수 포인터
    void (*mergeSort)(struct Sort *sort);   // 합병 정렬 함수 포인터
    void (*heapSort)(struct Sort *sort);    // 힙 정렬 함수 포인터
    void (*print)(struct Sort *sort);       // 출력 함수 포인터
    void (*termination)(struct Sort *sort); // 종료 함수 포인터

    // 변수 (속성)
    int arr[MAX_SIZE];  // 정렬에 사용될 배열
    int temp[MAX_SIZE]; // 합병정렬과 퀵정렬을 위해 사용되는 배열
    int length;         // 배열의 크기
    int startIndex;     // arr의 시작 색인
    int lastIndex;      // arr의 마지막 색인
};

// 함수 원형 선언 부분
void funcSelectSort(struct Sort *sort);  // 선택 정렬 함수
void funcInsertSort(struct Sort *sort);  // 삽입 정렬 함수
void funcbubbleSort(struct Sort *sort);  // 거품 정렬 함수
void funcQuickSort(struct Sort *sort);   // 빠른 정렬 함수
void funcMergeSort(struct Sort *sort);   // 합병 정렬 함수
void funcHeapSort(struct Sort *sort);    // 힙 정렬 함수
void funcPrint(struct Sort *sort);       // 출력 함수
void funcTermination(struct Sort *sort); // 종료 함수

struct Sort *sort_init(void)
{ // Sort 클래스 인스턴화 함수

    struct Sort *sort = (struct Sort *)malloc(sizeof(struct Sort)); // 동적 할당
    // 함수[메소드] (기능)
    sort->selectSort = funcSelectSort; // 함수 원형 포인터에 함수 주소 대입 ( 아래도 이 코드와 같음 )
    sort->insertSort = funcInsertSort;
    sort->bubbleSort = funcbubbleSort;
    sort->quickSort = funcQuickSort;
    sort->mergeSort = funcMergeSort;
    sort->heapSort = funcHeapSort;
    sort->print = funcPrint;
    sort->termination = funcTermination;

    //변수 (속성)
    sort->length = SIZE;        // length에 SIZE 삽입
    sort->startIndex = 0;       // startIndex는 0
    sort->lastIndex = SIZE - 1; // lastIndex는 SIZE - 1

    return sort; // 초기화를 다한 Sort 를 반환.
}

// BUBBLE SORT

// void funcbubbleSort(...)
// bubble sort의 시작점 이며, 정렬을 수행합니다. (반환값은 존재하지 않으며, 순차적입니다. )
void funcbubbleSort(struct Sort *sort)
{

    for (int i = 0; i < sort->length; ++i)             // i(0) ~ (arr의 길이 - 1)
        for (int j = 0; j < sort->length - i - 1; ++j) // j(0) ~ (arr의 길이 - i - 1)
            if (sort->arr[j] > sort->arr[j + 1])       // 가정 : arr[j] > [j + 1]
                SWAP(sort->arr[j], sort->arr[j + 1]);  // SWAP!
    return;
}

// SELECT SORT

// void funcSelectSort(...)
// Select Sort의 시작점 이며, 정렬을 수행합니다. (반환값은 존재하지 않으며 순차적입니다.)
void funcSelectSort(struct Sort *sort)
{

    int min;
    for (int i = 0; i < sort->length - 1; ++i)
    {                                              // i(0) ~ (arr의 길이 - 2)
        min = i;                                   // min = i (min은 값이 아닌 색인[index]을 저장합니다.)
        for (int j = i + 1; j < sort->length; ++j) // j(i+1) ~ (arr의 길이 -1)
            if (sort->arr[j] < sort->arr[min])     // 가정 : arr[j] > arr[min]
                min = j;                           // min = j

        SWAP(sort->arr[min], sort->arr[i]); // 제일 작은 값을 i색인(index) 값 이랑 교환
    }

    return;
}

// INSERT SORT

// void funcInsertSort(...)
// Insert Sort의 시작점 이며, 정렬을 수행합니다. (반환값은 존재하지 않으며 순차적입니다.)
void funcInsertSort(struct Sort *sort)
{
    int key;
    for (int i = 1; i < sort->length; ++i)
    {                       // i(1) ~ (arr의 크기 - 1)
        key = sort->arr[i]; // key = arr[i]
        int j = i - 1;      // j = i - 1;
        while (j >= 0 && sort->arr[j] > key)
        {                                    // j >= 0 && arr[j] > key
            sort->arr[j + 1] = sort->arr[j]; // 앞에 덮어쓰기
            --j;                             // 뒤칸으로 가기
        }
        sort->arr[j + 1] = key; // 값 대입
    }

    return;
}

// QUICK SORT

// void partition(...)
// Quick sort에 분활부분을 담당하며, pivot 기준으로 왼쪽은 작은 값들, 오른쪽은 큰 값들로 정렬됩니다. (반환값 pivot의 색인(index)를 반환합니다, 순차적입니다.)
int partition(struct Sort *sort, int left, int right)
{
    int pivot = sort->arr[right]; // 배열의 맨 오른쪽 값을 pivot으로 설정합니다.
    int i = (left - 1);           // i의 값은 left - 1 (작은 값을 추적함)

    for (int j = left; j <= right - 1; ++j)
    { // j(left) ~ right - 1
        if (sort->arr[j] <= pivot)
        { // 가정 : arr[j] <= pivot
            ++i;
            SWAP(sort->arr[i], sort->arr[j]); // arr[i] 랑 arr[j] 교환
        }
    }
    SWAP(sort->arr[i + 1], sort->arr[right]); // pivot이랑 i + 1 을 교환 -> pivot 기준으로 왼쪽에는 pivot보다 작은 값들, 오른쪽에는 pivot보다 큰 값들
    return (i + 1);                           // pivot의 위치 반환
}

// funcQuickSort funcQuickSortStart를 호출하는 함수 입니다. 반환형은 void 이며, 오직 함수 호출만 담당합니다.
// funcQuickSortStart를 바로 호출하지 않는 이유. 매인 문에서 Sort 클래스(구조체)를 인스턴스화(생성) 했을 때 간결한 호출을 위해
// 일부로 funcQickSortStart를 호출하지 않고 funcQickSort를 호출하게 만들었습니다.
void funcQuickSort(struct Sort *sort)
{
    funcQuickSortStart(sort, sort->startIndex, sort->lastIndex); // funcQuickSortStart 함수 호출

    return;
}

// void funcQuickSort(...)
// Quick sort의 시작점이며,정복을 시행하며, 분활 함수를 호출합니다.(반환값 pivot의 색인(index)를 반환합니다, 순차적입니다.)
void funcQuickSortStart(struct Sort *sort, int left, int right)
{
    if (left < right)
    { // 가정 : 원소 개수 판단 (원소의 개수가 하나 초과이면 TRUE, 원소의 개수가 하나면 FALSE)

        int pivot = partition(sort, left, right); // 분활 : partition 함수는 pivot 의 색인(index)를 반환합니다.

        funcQuickSortStart(sort, left, pivot - 1);  // 정복 : left ~ pivot - 1 부분을 정복합니다.
        funcQuickSortStart(sort, pivot + 1, right); // 정복 : pivot + 1 ~ right 부븐을 정복합니다.
    }

    return;
}
// MERGE SORT

// void merge(...)
// Merge sort에 결합부분을 담당하며, 2개의 배열을 정렬하여 합병합니다. (반환값은 존재하지 않으며, 순차적입니다.)
void merge(struct Sort *sort, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;

    // 분활 정렬된 arr를 합병
    while (i <= mid /*mid 기준으로 앞의 배열 판단*/ && j <= right /*mid 기준으로 뒤의 배열 판단*/)
    {
        if (sort->arr[i] <= sort->arr[j])     // 가정 : mid 기준으로 앞의 배열의 i 번째 값 <= mid 기준으로 뒤의 배열의 j 번째 값
            sort->temp[k++] = sort->arr[i++]; // temp 배열에 삽입
        else
            sort->temp[k++] = sort->arr[j++]; // temp 배열에 삽입
    }

    // 남아 있는 레코드 일괄 복사
    if (i > mid)                            // 가정 : mid 기준으로 앞의 배열을 다 복사 했다면
        for (int l = j; l <= right; ++l)    // j ~ right
            sort->temp[k++] = sort->arr[l]; // 복사
    else                                    // mid 기준으로 뒤의 배열을 다 복사 했다면
        for (int l = i; l <= mid; ++l)      // i ~ mid
            sort->temp[k++] = sort->arr[l]; // 복사

    // temp의 배열의 값을 arr에 재복사
    for (int l = left; l <= right; ++l) // 시작 ~ 끝
        sort->arr[l] = sort->temp[l];   // 복사

    return;
}

// MERGE SORT

// funcMergeSortStart를 호출하는 함수 입니다. 반환형은 void 이며, 오직 함수 호출만 담당합니다.
// 바로 funcMergeSortStart를 호출하지 않는 이유는 위 funcQuickSort와 같습니다.
void funcMergeSort(struct Sort *sort)
{
    funcMergeSortStart(sort, sort->startIndex, sort->lastIndex);
    return;
}

// void funcMergeSort(...)
// Merge sort의 시작점 이며, 분활과 정복을 시행하고 결합 함수를 호출합니다. (반환값은 존재하지 않으며, 재귀입니다. )
void funcMergeSortStart(struct Sort *sort, int left, int right)
{

    if (left < right)
    { // 가정 : 원소 개수 판단 (원소의 개수가 하나 초과이면 TRUE, 원소의 개수가 하나면 FALSE)

        int mid = (left + right) / 2; // 분활 : mid = 배열의 중간 색인(index)값

        funcMergeSortStart(sort, left, mid);      // 정복 : mid 기준으로 앞의 배열
        funcMergeSortStart(sort, mid + 1, right); // 정복 : mid 기준으로 뒤의 배열

        merge(sort, left, mid, right); // 결합 : 정렬된 2개의 부분 배열을 합병함
    }

    return;
}

// 최대 힙 트리를 만드는 함수 입니다.
void insertMaxHeap(struct Sort *sort, int item, int heapIndex)
{

    int i = heapIndex;                             // i = heapIndex
    while ((i != 1) && (item > sort->temp[i / 2])) // heapIndex가 조상 노드가 아니고, 대입할 값이 부모 노드보다 크다면 while 실행
    {
        sort->temp[i] = sort->temp[i / 2]; // temp[heapIndex] = temp[i/2](부모)
        i /= 2;                            // heapIndex /= 2
    }
    sort->temp[i] = item; // 최종 heapIndex에 대입

    return;
}

// 최대 힙 삭제 함수 입니다. 최대힙 값을 삭제한 것을 반환합니다.
int deleteMaxheap(struct Sort *sort, int heapIndex)
{
    int parent, child, item, temp;
    item = sort->temp[1];         // item = 조상 노드
    temp = sort->temp[heapIndex]; // temp = temp[heapIndex]
    parent = 1, child = 2;        // parent랑 child가 왔다갔다 하면서 하면서 값을 변경시킴. 그러므로 필요함.
    while (child <= heapIndex)    // child <= heapIndex 가 작다면 while문 참.
    {
        if ((child < heapIndex) && (sort->temp[child] < sort->temp[child + 1])) // child가 heapIndex보다 작고 temp[child] 가 temp[child+1] 가 작다면
            child++;                                                            // child ++;
        if (temp >= sort->temp[child])                                          // child가 temp[child] 보다 작거나 같으면
            break;                                                              // break;
        sort->temp[parent] = sort->temp[child];                                 // temp[parent] = temp[child] 대입
        parent = child;                                                         // parent = child;
        child *= 2;                                                             // child * 2
    }
    sort->temp[parent] = temp; // temp[parent] = temp 대입
    return item;               // itep 반환
}

// 최대 힙 정렬의 시작점 이며, 최대 힙 생성, 최대 힙 삭제를 호출합니다. (반환값은 존재하지 않으며, 순차적입니다. )
void funcHeapSort(struct Sort *sort)
{
    int heapIndex = 0;                     // heapIndexd의 초기값은 0;
    for (int i = 0; i < sort->length; ++i) // i ~ strlen(arr) - 1
    {
        heapIndex++;                                  //  heapIndex++
        insertMaxHeap(sort, sort->arr[i], heapIndex); // insertMaxHeap 호출 -> 최대 힙 트리 생성
    }

    for (int i = sort->length - 1; i >= 0; --i) // 24 ~ 0
    {
        sort->arr[i] = deleteMaxheap(sort, heapIndex); // deleteMaxHeap 호출 -> 최대 힙 트리 삭제
        heapIndex--;                                   // heapIndex--
    }

    return;
}

// Array print
// arr의 내용을 출력해주는 함수 입니다.
void funcPrint(struct Sort *sort)
{
    for (int i = 0; i < sort->length; ++i) // 0 ~ 24
        printf("%d ", sort->arr[i]);       // 출력

    return;
}

void funcTermination(struct Sort *sort)
{
    free(sort); // 동적 할당 해제
    return;
}