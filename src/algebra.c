#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    for(int i=0;i<row;i++){
        int j=0;
        for(j=0;j<col;j++){
        m.data[i][j]=0;
        }
    }
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    if(a.rows!=b.rows||a.cols!=b.cols){
        printf("Error: Matrix a and b must have the same rows and cols.");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows,a.cols);
    for(int i=0;i<a.rows;i++){
        int j=0;
        for(j=0;j<a.cols;j++){
            result.data[i][j]=a.data[i][j]+b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
    if(a.rows!=b.rows||a.cols!=b.cols){
        printf("Error: Matrix a and b must have the same rows and cols.");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows,a.cols);
    for(int i=0;i<a.rows;i++){
        int j=0;
        for(j=0;j<a.cols;j++){
            result.data[i][j]=a.data[i][j]-b.data[i][j];
        }
    }
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b) //乘法
{
    // ToDo
    if (a.cols!= b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows,b.cols);
    for(int i=0;i<a.rows;i++){
        int j=0;
        for(j=0;j<b.cols;j++){
            result.data[i][j]=0;
            for(int k=0;k<a.cols;k++){
                result.data[i][j]+=a.data[i][k]*b.data[k][j];
            }
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k) //数乘
{
    // ToDo
    Matrix result =create_matrix(a.rows,a.cols);
    for(int i=0;i<a.rows;i++){
        int j=0;
        for(j=0;j<a.cols;j++){
            result.data[i][j]=k*a.data[i][j];
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a) //转置
{
    // ToDo
    Matrix result =create_matrix(a.cols,a.rows);
    int i=0;
    for(i=0;i<a.cols;i++){
        int j=0;
        for(j=0;j<a.rows;j++){
            result.data[i][j]=a.data[j][i];
        }
    }
    return result;
}

//计算余子式
Matrix get_submatrix(Matrix a, int row, int col){
    Matrix sub=create_matrix(a.rows-1,a.cols-1);
    int sub_i=0,sub_j=0;
    for(int i=0;i<a.rows;i++){
        if(i==row) continue;
        sub_j=0;
        int j=0;
        for(j=0;j<a.cols;j++){
            if(j==col) continue;
            sub.data[sub_i][sub_j]=a.data[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}

double det_matrix(Matrix a) //行列式
{
    // ToDo
    if(a.rows!=a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    if(a.rows==1){
        return a.data[0][0];
    }
    if(a.rows==2){
        return a.data[0][0]*a.data[1][1]-a.data[0][1]*a.data[1][0];
    }
    double det=0;
    int j=0;
    for(j=0;j<a.cols;j++){
        Matrix sub=get_submatrix(a,0,j);
        det=det+pow(-1,j)*a.data[0][j]*det_matrix(sub);
    }

    return det;
}

Matrix inv_matrix(Matrix a) //逆
{
    // ToDo
    if(a.rows!=a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    double det=det_matrix(a);
    if(det==0){
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    Matrix result=create_matrix(a.rows,a.cols);
    for(int i=0;i<a.rows;i++){
        int j=0;
        for(j=0;j<a.cols;j++){
            Matrix sub=get_submatrix(a,j,i);
            result.data[i][j]=pow(-1,i+j)*det_matrix(sub)*(1/det);
        }
    }
    return result;
}

int rank_matrix(Matrix a) //秩
{
    // ToDo
    int rank=(a.rows<a.cols)? a.rows:a.cols;
    for(int i=0;i<a.rows;i++){
        if(a.data[i][i]==0){
            int c=1;
            while((i+c)<rank && a.data[i+c][i+c]==0) c++;
            if((i+c)==rank){
                rank--;
                int k=0;
                for(k=0;k<a.rows;k++){
                    a.data[k][i]=a.data[k][rank];
                }
                i--;
            }else {
                int j=0;
                for(j=0;j<a.cols;j++){
                    double temp=a.data[i][j];
                    a.data[i][j]=a.data[i+c][j];
                    a.data[i+c][j]=temp;
                }
            }
        }
        for(int j=i+1;j<a.cols;j++){
            double factor=a.data[j][i]/a.data[i][i];
            for(int k=i;k<a.rows;k++){
                a.data[j][k]-=a.data[i][k]*factor;
            }
        }
    }
        return rank;
}

double trace_matrix(Matrix a) //迹
{
    // ToDo
    if(a.rows!=a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    double trace=0;
    for(int i=0;i<a.rows;i++){
        trace=trace+a.data[i][i];
    }

    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        int j=0;
        for (j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}