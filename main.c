#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Luu gia tri bang #define
#define MAX_ROW 9
#define MAX_COLUMN 9
#define MAX 10

//Tạo các cấu trúc và biến cục bộ
typedef struct POINT {
    int row;            //Tọa độ x
    int column;         //Tọa đọ y
    int value;          //Gía trị 0 hoặc 1
    bool visited;       //đánh dấu nút đã đi qua
    struct POINT *prev; //Con trỏ trỏ đến nút liền trước nó trước khi đi qua nút này
} point_t;
//Khai báo kiểu cấu trúc cho hàng đợi
typedef struct
{
   point_t data[MAX];//Lưu trữ nút
    int front;//Chỉ số đầu của hàng đợi
    int rear;//Chỉ số cuối của hàng đợi
}Queue;
point_t matrix[MAX_ROW][MAX_COLUMN];
bool checkCoordinate(int x, int y);
int findSurroundingPoint(int x, int y, point_t surroundingPnt[]);
void findShortestPath (int x, int y);
//Hàng đợi gồm 5 hàm cơ bản:
//Khởi tạo hàng đợi
void initQueue(Queue *q)
{
       q->front = 0;    //hệ số đầu của hàng
       q->rear = -1;    //Hệ số cuối của hàng
}
//Kiểm tra hàng rỗng
int isEmpty(Queue q)
{
       return (q.rear < q.front);   //Khi front>rear -> ham rỗng
}
//Kiểm tra hàng đầy
int isFull(Queue q)
{
    //Neu rear == MAX-1 -> hàng đẫ đầy(chỉ số cuối hàng đợi lớn hơn số lượng phần tử tối đa mà hàng đợi có thể chứa)
    if(q.rear == MAX - 1) {
        return 1;
    }
       else return 0;
}
//Cho thêm phần tử vào hàng
void enQueue(Queue *q, point_t x)
{

    //Nếu hàm chưa đầy -> thêm 1 phần tử vào mảng data + tang 1 gia tri cho rear
      if (!isFull(*q)) {

            q->rear = q->rear + 1;
            q->data[q->rear] = x;
       }
       //Nếu hàng đã đầy
       if(q->rear == MAX - 1)
        {
            //Bỏ những phần tử mà front đã đi qua
                  for(int i = q->front; i <= q->rear; i++){
                           q->data[i - q->front] = q->data[i];
                  }
                  q->rear = MAX - q->front;
                  q->front = 0;
        }
}
//Lấy phần tử đầu tiên ra khỏi hàng
point_t deQueue(Queue *q) {
    point_t d;
    //Nếu hàng không rỗng
    if (!isEmpty(*q)) {
       d = q->data[q->front];
       q->front = q->front +1;
       //Tăng front lên 1 và chuyển dữ liệu cho biến d
    }
    //Nếu hàng rỗng
    if (q->front > q->rear) {
        initQueue(q);//Đặt lại front va rear
    };
    return d;
}

//Hàm kiểm tra toa đọ dong,cot co nằm trong mảng đã khai báo
bool checkCoordinate(int dong, int cot) {
    bool ret = false;
    if (dong < MAX_ROW  &&cot <MAX_COLUMN && 0<=dong && 0<=cot) //Nếu 0<=dong<9 va 0<=cot<9 thi dong,cot có nằm trong mảng
        {
            ret = true;
        }
    return ret;
}

//Tìm những điểm quanh điểm dong,cot có giá tri bằng 1 va lưu toa độ những điểm đó vao mảng surroundingPnt
int findSurroundingPoint(int dong, int cot, point_t surroundingPnt[]){
 int tempCnt = 0;
                //Kiểm tra điểm nừm bên phải dong,cot nằm trong mảng và điểm đó có giá trị =1
                if ((checkCoordinate(dong, cot+1) == true) && (matrix[dong][ cot+1].value == 1)){
                            surroundingPnt[tempCnt ] = matrix[dong][cot+1];
                            tempCnt++;
                }
                //Kiểm tra điểm nừm bên dưới dong,cot nằm trong mảng và điểm đó có giá trị =1
                if ((checkCoordinate(dong+1, cot) == true) && (matrix[dong+1][cot].value == 1)) {
                            surroundingPnt[tempCnt ] = matrix[dong+1][cot];
                            tempCnt++;
                }
                //Kiểm tra điểm nừm bên trái dong,cot nằm trong mảng và điểm đó có giá trị =1
                if ((checkCoordinate(dong, cot-1) == true) && (matrix[dong][cot-1].value == 1)) {
                            surroundingPnt[tempCnt ] = matrix[dong][cot-1];
                            tempCnt++;
                }
                //Kiểm tra điểm nừm bên trên dong,cot nằm trong mảng và điểm đó có giá trị =1
                if ((checkCoordinate(dong-1, cot) == true) && (matrix[dong-1][cot].value == 1)) {
                            surroundingPnt[tempCnt ] = matrix[dong-1][ cot];
                            tempCnt++;
                }
            return tempCnt; //số điểm có thể đến được
}
//Hàm tìm đường đi ngắn nhất
void findShortestPath (int dong, int cot)
{
        int count;
        int row_temp,col_temp;
        point_t temp;
        point_t pp[4];
        Queue queue;
        Queue *q=&queue;
        initQueue(q);//Khởi tạo hàng
        matrix[0][0].visited=true; //Đánh dấu O(0,0) là đã qua
        enQueue(q,matrix[0][0]); //Cho điểm đầu tiên O(0,0) vào hàng
        bool found=false;
        printf("\nToa do cac nut xung quanh tren duong di cua nut duoc xet:\n");
        //Tìm điểm cần tìm và lưu lại những điểm đã đi qua vào con trỏ của điểm tiếp theo
        while (isEmpty(queue) == false&&found==false) //Nếu không còn phần tử nào trong hàng hoặc tìm thấy điểm cần tìm => thóat ra khoi loop
        {
            temp=deQueue(q);//Lấy phần tử đầu của hàng lưu vào biến temp
            count=findSurroundingPoint(temp.row,temp.column,pp);//Gọi hàm surroundingPnt() để tìm các nút xung quanh pp[] của nút temp vừa lấy ra khỏi hàng đợi;
            for(int i=0;i<count;i++)//Dùng vòng for duyệt lần lượt các nút chung quanh vừa được tìm thấy ở trên
                {

                if(matrix[pp[i].row][pp[i].column].visited==false)
                    {

                        matrix[pp[i].row][pp[i].column].visited=true; //Đánh dấu nút đã đi qua
                        matrix[pp[i].row][pp[i].column].prev = &matrix[temp.row][temp.column]; //Lưu địa chỉ của điểm trước đó vào

                        if(pp[i].row==dong&&pp[i].column==cot)//Nếu điểm có cùng tọa độ với điểm cần tìm thì thoát ra khỏi vòng lặp
                        {
                            found=true;
                            break;
                        }
                        else
                        {

                            enQueue(q,matrix[pp[i].row][pp[i].column]);//Cho điểm đó vào hàng
                           printf("(%d,%d)->",matrix[pp[i].row][pp[i].column]);
                        }
                    }
                }
        }
        //Vòng lặp tìm ra đường đi nhanh nhất vì các đường đi đều bắt đầu ở một điểm và tăng lên giảm đi lần lượt
        if (found == true)
	{
        point_t *m = &matrix[dong][cot];
        int sum = 0;
        point_t mang[100];

        while (m != NULL)
		{
            mang[sum]= * m;
            m = m->prev;
            sum++;
        }

        printf("\n\nDuong di ngan nhat tu O(0, 0) den A(%d, %d) co do dai la %d o:\n", dong, cot, sum);
        int i = 0;
        for(i = sum-1; i >= 0; i--)
		{
            printf("(%d, %d) ", mang[i].row, mang[i].column);
            if (i != 0)
			{
                 printf("-> ");
            }
        }
    }
	else {
        printf("\nKhong co duong di tu O(0, 0) den A(%d, %d)", dong, cot);
    }
}

int main()
{
printf("\nCHUONG TRINH TIM DUONG DI NGAT NHAT TU 0(0,0) DEN A(dong,cot):\n");
printf("\nMa tran 9x9 bieu dien cho mat phang hai chieu:\n");
//Luu ma trận đã cho trước vào mảng matrix
int array[]=
    {1,0,0,0,1,0,1,1,0,
     1,1,0,1,1,1,0,0,1,
     0,1,0,1,1,0,1,0,1,
     0,1,1,0,0,1,0,1,1,
     0,0,1,0,1,0,1,0,0,
     1,1,1,0,0,0,0,1,1,
     1,0,1,1,1,1,1,0,0,
     1,1,1,0,0,0,1,0,1,
     0,0,0,1,1,1,1,1,0};
// Sử dung 2 loop để luu vào mảng 2 chiều
for(int i=0,e=0;i<MAX_ROW;i++)
{
    for(int j=0;j<MAX_COLUMN;j++)
    {
        matrix[i][j].value=array[e];
        matrix[i][j].column=j;
        matrix[i][j].row=i;
        matrix[i][j].visited=false;
        e++;
    }
}
//Tương tự giá tri cuả từng phần tử trong mảng
for(int i=0;i<MAX_ROW;i++)
{
    for(int j=0;j<MAX_COLUMN;j++)
    {
        printf("%d ",matrix[i][j].value);
    }
        printf("\n");
}

int dong,cot;     //Toa dộ dược nhập vào
printf("\nTao do cua 0 xuat phat la 0(0,0).\n");
//Nhập tọa độ đó
while(1)
{
printf("\nHay nhap toa do cua 0 den A:\n");
printf("Nhap dong: ");
scanf("%d",&dong);
printf("Nhap cot: ");
scanf("%d",&cot);
if(checkCoordinate(dong,cot)) //Nếu dong,cot thuộc mảng thi thoát ra khỏi loop
    break;
else
    printf("Giatri cua dong phai tu 0 den 8!\n"); //Neu dong,cot không thuộc maảng thì lặp lai loop
    printf("Gia tri cua cot phai tu 0 den 8!\n");
}
findShortestPath(dong,cot);
}
