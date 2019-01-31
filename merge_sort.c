#include <stdio.h>

int num_elems;

void print_array(int* arr)
{
    int i;
    for(i=0;i<num_elems;i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int swap(int* a, int left, int right)
{
    int temp;
    /* swap the elements */
    temp = a[left];
    a[left] = a[right];
    a[right] = temp;
}


int partition(int* a, int low, int high)
{
    int left = low;
    int right = high;
	
	/* first element as pivot */
    int pivot_value = a[low];
	
    /* start 1 element after pivot */	
	left++;
    while(1)
    {
        while(a[left] < pivot_value && left<=right)
        {
            left++;
        }
        while(a[right] > pivot_value && right>=left)
        {
            right--;
		}
		
        if(left < right)
        {
            swap(a, left, right);
        }
        else
        {
            break;
        }
    }

    /* put pivot into the middle position of both the arrays */
    a[low] = a[right];
    a[right] = pivot_value;

    return right;
}


void quicksort(int* arr, int low, int high)
{
    int pivot;
	
    if(low < high)
    {
        pivot = partition(arr, low, high);
        quicksort(arr, low, pivot-1);
        quicksort(arr, pivot+1, high);
    }
}


int main()
{
    int arr[] = {15, 20, 1 ,99 , 100, 7, 12};
    num_elems = sizeof(arr)/sizeof(int);
	
    quicksort(arr, 0, num_elems-1);
    print_array(arr);
}
