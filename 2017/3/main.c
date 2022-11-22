#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

int is_perfect_odd_square(int n);
int find_distance_to_odd_perfect_square(int);
int find_number_of_steps(int n);

int main(int argc, char *argv[]){
	int input = 5;
	// if (is_perfect_odd_square(input)){
	// 	printf("%d\n", find_number_of_steps(input));
	// 	return 0;
	// }
	int steps = find_distance_to_odd_perfect_square(input);
	printf("%d\n", steps);
	return 0;
}

int find_distance_to_odd_perfect_square(int n){
	int l = n;
	int r = n;

	while((is_perfect_odd_square(l) == 0 && (is_perfect_odd_square(r) == 0))){
		if(l > 0) l--;
		r++;
	}
	if (is_perfect_odd_square(l) == 1){
		return abs((l - n));
	}
	return abs((r - n));
}

int is_perfect_odd_square(int n){
	float x = sqrt(n);
	if (pow(x, 2) == n && ((int)n % 2 != 0)) return 1;
	return 0;
}

int find_number_of_steps(int n){
	int result = 0;
	for(int i = 1; i <= sqrt(n); i++){
		int y = pow(i, 2);
		if (y % 2 != 0) result += 1;
	}
	return result;
}