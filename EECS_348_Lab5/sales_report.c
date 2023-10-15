#include <stdio.h>

void fileparser(char *filename, float *saleslist, int row){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error: File unable to be opened. /n");
        return;
    }
    for (int j = 0; j < row; j++){
        if (fscanf(file, "%f", &saleslist[j]) != 1) {
            printf("Error: Unable to read number from file.\n");
            break;
        }
    }
    fclose(file);
}

void salesreport(char **monthlist, float *saleslist, int row) {
    printf("\nMonthly sales report for 2022:\n");
    printf("Month \t   Sales\n");
    for (int i = 0; i < row; i++) {
        printf("%-10s $%.2f\n", monthlist[i], saleslist[i]);    
    }
}

int minsales(float *saleslist, int row) {
    int min = 0;
    for (int c = 0; c < row; c++) {
        if (saleslist[c] < saleslist[min]) {
            min = c;
        }
    }
    return min;
}

int maxsales(float *saleslist, int row) {
    int max = 0;
    for (int d = 0; d < row; d++) {
        if (saleslist[d] > saleslist[max]) {
            max = d;
        }
    }
    return max;
}


float avg(float *saleslist, int row) {
    float total_sum = 0.00;
    float total_average = 0.00;
    for (int e = 0; e < row; e++) {
        total_sum += saleslist[e];
    }
    total_average = total_sum / row;
    return total_average;
}

void salessummary(char **monthlist, float *saleslist, int min, int max, float average){
    printf("\nSales Summary\n");
    printf("Minimum sales: \t $%.2f (%s)\n", saleslist[min], monthlist[min]);
    printf("Maximum sales: \t $%.2f (%s)\n", saleslist[max], monthlist[max]);
    printf("Average sales: \t $%.2f \n\n", average);
}

void movingavg(char **monthlist, float *saleslist, int row) {
    int monthlast = 6;
    printf("Six-Month Moving Average Report:\n");
    while (monthlast < row+1) {
        float sum = 0.00;
        float avge = 0.00;
        for (int f = monthlast - 6; f < monthlast; f++) {
            sum += saleslist[f];
        }
        avge = sum / 6;
        printf("%-8s - %-10s $%.2f \n", monthlist[monthlast - 6], monthlist[monthlast - 1], avge);
        monthlast++;
    }
}
    
void ascendorder(float *saleslist, char **monthlist, int row) {
    for (int i = 0; i < row; i++) {
        for (int j = i + 1; j < row; j++) {
            if (saleslist[i] > saleslist[j]) {
                float temp = saleslist[i];
                saleslist[i] = saleslist[j];
                saleslist[j] = temp;
                char *tempM = monthlist[i];
                monthlist[i] = monthlist[j];
                monthlist[j] = tempM;
            }
        }
    }
    printf("\nSales Report (Highest to Lowest:)\n");
    printf("  Month      Sales\n");
    for (int i = row - 1; i >= 0; i--) {
        printf("%-10s $%.2f \n", monthlist[i], saleslist[i]);
    }
}
    
int main() {
    char *monthlist[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    float saleslist[12];
    int row = 12; 
    char filename[50];

    printf("Enter filename: \n");
    printf("[Make sure the file contains 12 numbers in their own row]\n");
    if (scanf("%49s", filename) != 1){
        printf("Error: Invalid input!\n");
        return 1;
    }

    fileparser(filename, saleslist, row);

    salesreport(monthlist, saleslist, row);
    
    int min = minsales(saleslist, row);
    int max = maxsales(saleslist, row);
    float average = avg(saleslist, row);
    
    salessummary(monthlist, saleslist, min, max, average);

    movingavg(monthlist, saleslist, row);
    
    ascendorder(saleslist, monthlist, row);

    printf("\n");

    return 0;
}