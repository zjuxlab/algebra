#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
    }
    else
    {
        Matrix sum;
        sum.cols = a.cols;
        sum.rows = a.rows;
        for (int i = 0; i < sum.rows; i++)
        {
            for (int j = 0; j < sum.cols; j++)
            {
                sum.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return sum;
    }
    return create_matrix(0, 0);
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
    }
    else
    {
        Matrix sub;
        sub.cols = a.cols;
        sub.rows = a.rows;
        for (int i = 0; i < sub.rows; i++)
        {
            for (int j = 0; j < sub.cols; j++)
            {
                sub.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return sub;
    }
    return create_matrix(0, 0);
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
    }
    else
    {
        Matrix res;
        res.rows = a.rows;
        res.cols = b.cols;
        for (int i = 0; i < res.rows; i++)
        {
            for (int j = 0; j < res.cols; j++)
            {
                double sum = 0;
                for (int k = 0; k < a.cols; k++)
                {
                    sum += a.data[i][k] * b.data[k][j];
                }
                res.data[i][j] = sum;
            }
        }
        return res;
    }
    return create_matrix(0, 0);
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix res;
    res.rows = a.rows;
    res.cols = a.cols;
    for (int i = 0; i < res.rows; i++)
    {
        for (int j = 0; j < res.cols; j++)
        {
            res.data[i][j] = k * a.data[i][j];
        }
    }
    return res;
    return create_matrix(0, 0);
}

Matrix transpose_matrix(Matrix a)
{
    Matrix res;
    res.rows = a.cols;
    res.cols = a.rows;
    for (int i = 0; i < res.rows; i++)
    {
        for (int j = 0; j < res.cols; j++)
        {
            res.data[i][j] = a.data[j][i];
        }
    }
    return res;
    return create_matrix(0, 0);
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    if (a.rows == 1)
    {
        return a.data[0][0];
    }
    else if (a.rows == 2)
    {
        double res;
        res = a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
        return res;
    }
    else
    {
        double res = 0;
        for (int j = 0; j < a.cols; j++)
        {
            Matrix temp;
            temp.rows = a.rows - 1;
            temp.cols = a.cols - 1;
            int m = 0, n = 0;
            for (int p = 0; p < a.rows - 1; p++)
            {
                for (int q = 0; q < a.cols; q++)
                {
                    if (q == j)
                        continue;
                    temp.data[m][n] = a.data[p][q];
                    n++;
                    if (n == temp.cols)
                    {
                        n = 0;
                        m++;
                    }
                }
            }
            res = res + a.data[a.rows - 1][j] * det_matrix(temp) * pow(-1, a.rows + j + 1);
        }
        return res;
    }
}

Matrix inv_matrix(Matrix a)
{
    if (a.cols != a.rows)
    {
        printf("Error: The matrix must be a square matrix.\n");
    }
    else if (det_matrix(a) == 0)
    {
        printf("The matrix is singular.\n");
    }
    else
    {
        double det = det_matrix(a);
        Matrix adj;
        adj.rows = a.rows;
        adj.cols = a.cols;
        for (int i = 0; i < adj.rows; i++)
        {
            for (int j = 0; j < adj.cols; j++)
            {
                Matrix temp;
                temp.rows = a.rows - 1;
                temp.cols = a.cols - 1;
                int m = 0, n = 0;
                for (int p = 0; p < a.rows; p++)
                {
                    if (p == j)
                        continue;
                    for (int q = 0; q < a.cols; q++)
                    {
                        if (q == i)
                            continue;
                        temp.data[m][n] = a.data[p][q];
                        n++;
                        if (n == temp.cols)
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
                adj.data[i][j] = pow(-1, i + j) * det_matrix(temp);
            }
        }
        return scale_matrix(adj, (1.0 / det));
    }
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
    int i = 0, j = 0;
    for (j = 0; j < a.cols;)
    {
        if (a.data[i][j] == 0)
        {
            int m;
            for (m = i + 1; m < a.rows; m++)
            {
                if (a.data[m][j] != 0)
                    break;
            }
            if (m == a.rows)
                j++;
            else
            {
                for (int n = 0; n < a.cols; n++)
                {
                    int temp = a.data[m][n];
                    a.data[m][n] = a.data[i][n];
                    a.data[i][n] = temp;
                }
                int x, y;
                double n;
                n = 1 / a.data[i][j];
                for (y = 0; y < a.cols; y++)
                {
                    a.data[i][y] = n * a.data[i][y];
                }
                for (x = 0; x < i; x++)
                {
                    n = -a.data[x][j] / a.data[i][j];
                    for (y = 0; y < a.cols; y++)
                    {
                        a.data[x][y] = a.data[x][y] + n * a.data[i][y];
                    }
                }
                for (x = i + 1; x < a.rows; x++)
                {
                    n = -a.data[x][j] / a.data[i][j];
                    for (y = 0; y < a.cols; y++)
                    {
                        a.data[x][y] = a.data[x][y] + n * a.data[i][y];
                    }
                }
                i++;
                j++;
            }
        }
        else
        {
            int x, y;
            double n;
            n = 1 / a.data[i][j];
            for (y = 0; y < a.cols; y++)
            {
                a.data[i][y] = n * a.data[i][y];
            }
            for (x = 0; x < i; x++)
            {
                n = -a.data[x][j] / a.data[i][j];
                for (y = 0; y < a.cols; y++)
                {
                    a.data[x][y] = a.data[x][y] + n * a.data[i][y];
                }
            }
            for (x = i + 1; x < a.rows; x++)
            {
                n = -a.data[x][j] / a.data[i][j];
                for (y = 0; y < a.cols; y++)
                {
                    a.data[x][y] = a.data[x][y] + n * a.data[i][y];
                }
            }
            i++;
            j++;
        }
    }
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            if (a.data[i][j] != 0)
                break;
        }
        if (j == a.cols)
            break;
    }
    return i;
}

double trace_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
    }
    else
    {
        double sum = 0;
        for (int i = 0; i < a.rows; i++)
        {
            sum += a.data[i][i];
        }
        return sum;
    }
    return 0;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}