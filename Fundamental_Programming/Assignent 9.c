#define MaxRow 10 //array-maximum no of rows
#define MinRow 1 //array-minimum no of rows
#define MaxCol 6 //array-maximum no of columns
#define MinCol 1 //array-minimum no of columns

#include <stdio.h>

int main()
{
    int RowSize, ColSize;
    int a[MaxRow][MaxCol],//1st input array
     b[MaxRow][MaxCol],//2nd input array
     c[MaxRow][MaxCol];//resulting array

//Functions declaration
        int ReadArraySize(int,int);
       void InitArray(int [][MaxCol], int[][MaxCol], int, int),
             InitArrayC(int [][MaxCol], int[][MaxCol], int[][MaxCol], int, int),
             DispResult(int [][MaxCol], int[][MaxCol], int[][MaxCol], int, int);

    printf("Please specify no. of rows of arrays: ");
    RowSize=ReadArraySize(MinRow,MaxRow);

    printf("Please specify no. of columns of arrays: ");
    ColSize=ReadArraySize(MinCol,MaxCol);
    printf("Array size is set to: [%d] [%d]\n", RowSize, ColSize);

    InitArray(a, b, RowSize, ColSize);//init arrays a & b

//find array c[][] = array a[][] + b[][]
    InitArrayC(a, b, c, RowSize, ColSize);

    DispResult(a, b, c, RowSize, ColSize);//display result

    printf( "please type any key to exit: ");
    getchar();

    return 0;
}


int ReadArraySize(int MinSize,int MaxSize) //read array size, row then column
{
    int size;
	do{
      	printf(" range[%d..%d] : ",MinSize,MaxSize);
	    scanf("%d", &size);
   	}while(size > MaxSize || size <= MinSize);

    return size;

}//end



void InitArray(int a[][MaxCol], int b[][MaxCol], int RowSize, int ColSize)
{
	int i, j;

	printf("\nInitializing arrays a and b..\n");
	for(i=0;i<RowSize;i++){
	    for(j=0;j<ColSize;j++){
        printf("First Matrix [%d][%d]: ",i,j);
        scanf("%d",&a[i][j]);
        }
	}
	for(i=0;i<RowSize;i++){
	    for(j=0;j<ColSize;j++){
        printf("Second Matrix [%d][%d]: ",i,j);
        scanf("%d",&b[i][j]);
	    }
	}
}//end




void InitArrayC(int a[][MaxCol], int b[][MaxCol], int c[][MaxCol], int RowSize, int ColSize)
{
	int i, j;

	printf("Calculating array c..\n\n");
	for(i=0;i<RowSize;i++)
	    for(j=0;j<ColSize;j++)
		c[i][j]= a[i][j]+ b[i][j];
}//end InitArrayC()



void DispResult(int a[][MaxCol], int b[][MaxCol], int c[][MaxCol], int RowSize, int ColSize)
{
	int i, j;

    for(i=0;i<RowSize;i++){
        for(j=0;j<ColSize;j++){
		printf("%4d",a[i][j]);
        }
        printf("\n");
	}
	puts("");
    for(i=0;i<RowSize;i++){
        for(j=0;j<ColSize;j++){
            printf("%4d",b[i][j]);
        }
        printf("\n");
    }
	puts("");


    for(i=0;i<RowSize;i++){
        for(j=0;j<ColSize;j++){
            printf("%4d",c[j][i]);
        }
        printf("\n");
    }
}//end DispResult()
