#include <stdio.h>
#include "algebra.h"

int main()
{
    while (1)
    {
        int frame;
        scanf("%d", &frame);
        if (frame == -1)
        {
            break;
        }
        int row, col;
        scanf("%d %d\n", &row, &col);
        Matrix a = create_matrix(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                scanf("%lf", &a.data[i][j]);
            }
        }
        scanf("%d %d\n", &row, &col);
        Matrix b = create_matrix(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                scanf("%lf", &b.data[i][j]);
            }
        }
        print_matrix(add_matrix(a, b));
        print_matrix(sub_matrix(a, b));
        print_matrix(mul_matrix(a, b));
        print_matrix(scale_matrix(a, 2));
        print_matrix(transpose_matrix(a));
        printf("%.2f\n", det_matrix(a));
        print_matrix(inv_matrix(a));
        printf("%d\n", rank_matrix(b));
        printf("%.2f\n", trace_matrix(a));
    }
    return 0;
}