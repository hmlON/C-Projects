#include <stdlib.h>
#include <stdio.h>

float* readMatrix(int numRows, int numCols);
float* rowAverage(float *matrix, int numRows, int numCols);
float* colAverage(float *matrix, int numRows, int numCols);
float overallAverage(float* matrix, int numRows, int numCols);
void printAverages(float *matrix, float *rowAve, float *colAve, float overallAve, int numRows, int numCols);

int main() {

    int isEnd;
    do{

        int numRows, numCols, err;
        //reading rows
        do{
            printf("Enter row dimension (must be between 1 and 5): ");
            err = scanf("%d", &numRows);
        }while((err != 1)||(numRows < 1)||(numRows > 5));
        //reading cols
        do{
            printf("Enter column dimension (must be between 1 and 5): ");
            err = scanf("%d", &numCols);
        }while((err != 1)||(numCols < 1)||(numCols > 5));

        //reading matrix
        float* arr = readMatrix(numRows, numCols);
        float* rowAverageArr = rowAverage(arr, numRows, numCols);
        float* colAverageArr = colAverage(arr, numRows, numCols);
        float overallAverageNum = overallAverage(arr, numRows, numCols);

        //printing averages
        printAverages(arr, rowAverageArr, colAverageArr, overallAverageNum, numRows, numCols);

        //freeing memory
        free(arr);

        //asking to continue
        printf("\nEnter 0 to continue with a new matrix\n");
        printf("Enter any other number to terminate: ");
        scanf("%d", &isEnd);

    } while(isEnd == 0);

    return 0;

}

float* readMatrix(int numRows, int numCols){
    // Dynamically allocate an array to hold a matrix of floats.
    // The dimension of the matrix is numRows x numCols.
    float* arr = (float*)malloc(numRows*numCols*sizeof(float));;

    // If the malloc fails, return NULL.
    if(arr == NULL)
        return NULL;

    // Otherwise, prompt the user to enter numRows*numCols values
    // for the matrix in by-row order. Store these values in the array.
    printf("Enter %d data values for %d x %d matrix, in by-row order\n", numCols*numRows, numRows, numCols);
    int i;
    for(i = 0; i < numCols*numRows; i++)
        scanf("%f", arr+i);

    // Return a pointer to the array.
    return arr;
}

float* rowAverage(float *matrix, int numRows, int numCols){
    // Dynamically allocate an array of floats with numRows elements.
    float* rowAverageArr = (float*)malloc(numRows*sizeof(float));

    // Return NULL if the memory allocation fails.
    if(rowAverageArr == NULL)
        return NULL;

    // Otherwise, for 0 <= i < numRows, set the ith element of the
    //new array to the mean of the values in the ith row of the array
    //pointed to by matrix. The dimension of the matrix is
    //numRows x numCols and its elements are stored in by-row order.
    int i, j;
    float rowSum;
    for (i = 0; i < numRows; i++) {
        rowSum = 0;
        for (j = 0; j < numCols; j++) {
            rowSum += matrix[i*numCols+j];
        }
        rowAverageArr[i] = rowSum / numCols;
    }

    return rowAverageArr;
}

float* colAverage(float *matrix, int numRows, int numCols){
    // Dynamically allocate an array of floats with numCols elements.
    float* colAverageArr = (float*)malloc(numCols*sizeof(float));

    // Return NULL if the memory allocation fails.
    if(colAverageArr == NULL)
        return NULL;

    // Otherwise, for 0 <= j < numCols, set the jth element of the
    // new array to the mean of the values in the jth column of the array
    //pointed to by matrix. The dimension of the matrix is
    //numRows x numCols and its elements are stored in by-row order.
    int i, j;
    float colSum;
    for (j = 0; j < numCols; j++) {
        colSum = 0;
        for (i = 0; i < numRows; i++) {
            colSum += matrix[i*numCols+j];
        }
        colAverageArr[j] = colSum / numRows;
    }

    return colAverageArr;

}

float overallAverage(float* matrix, int numRows, int numCols){
    float sum = 0;
    int i,j;
    for(i = 0; i < numRows; i++)
        for (j = 0; j < numCols; j++)
            sum += matrix[i*numCols+j];

    // Return the mean value of the elements of the array pointed
    // to by matrix. The dimension of the matrix is numRows x numCols.
    return sum / (numRows*numCols);
}

void printAverages(float *matrix, float *rowAve, float *colAve, float overallAve, int numRows, int numCols){
    // Print the matrix with the row average displayed to the right of each row
    // and the column average displayed below each column.
    int i,j;
    for(i = 0; i < numRows; i++){
        for (j = 0; j < numCols; j++) {
            printf("%.2f ", matrix[i*numCols+j]);
        }
        printf("%-8.2f\n", rowAve[i]);
    }
    printf("\n");
    for(i = 0; i < numCols; i++){
        printf("%.2f ", colAve[i]);
    }
    printf("\n");

    // Also print the overall average
    printf("Overall average is: %f\n", overallAve);
}
