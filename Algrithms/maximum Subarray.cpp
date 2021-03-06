#include<stdio.h>
#include<stdlib.h>

void doarray(int A[], int a, int b, int c){
	A[0] = a;
	A[1] = b;
	A[2] = c;
}

int* find_max_cross_subarray(int A[], int low, int mid, int high){
	int left_sum, right_sum, sum,max_left, max_right, i;
	int arr[3] = {0};
	left_sum = -1000;
	sum = 0;
	for(i = mid; i>=low; i--){
		sum = sum + A[i];
	
		if(sum>left_sum){
			left_sum = sum;
			max_left = i;
		}
	}
	right_sum = -1000;
	sum = 0;
	for(i = mid+1; i<=high; i++){
		sum = sum + A[i];
	
		if(sum>right_sum){
			right_sum = sum;
			max_right = i;
		}
	}

	doarray(arr,max_left,max_right,left_sum + right_sum);
	/*arr[0] = max_left;
	arr[1] = max_right;
	arr[2] = left_sum + right_sum;*/
	return arr;
}

int * find_subarray(int A[], int low, int high){
	int arr1[3] = {0}, *p;
	int mid, left_low, left_high, left_sum, right_low, right_high, right_sum, cross_low, cross_high, cross_sum;
	if(high == low){
		doarray(arr1,low,high,A[low]);
		return arr1;
	}else{
		mid = (low + high)/2;
	}
	p = find_subarray(A, low, mid);
	left_low = *p;
	left_high = *(p+1);
	left_sum = *(p+2);

	p = find_subarray(A, mid+1, high);
	right_low = *p;
	right_high = *(p+1);
	right_sum = *(p+2);

	p = find_max_cross_subarray(A,low, mid,high);
	cross_low = *p;
	cross_high = *(p+1);
	cross_sum = *(p+2);

	if(left_sum >= right_sum && left_sum>= cross_sum){
		doarray(arr1, left_low,left_high,left_sum);
		return arr1;
	}

	else if(right_low >= left_sum && right_sum>= cross_sum){
		doarray(arr1, right_low,right_high,right_sum);
		return arr1;
	}
	else{
		doarray(arr1, cross_low,cross_high,cross_sum);
		return arr1;
	}

}

int main(){

	int A[101], n, *p;
	scanf("%d",&n);
	for(int i = 1; i<=n; i++){
		scanf("%d", &A[i]);
	}
	p = find_subarray(A, 1, n);
	printf("%d %d %d", *p, *(p+1),*(p+2));

	return 0;
}