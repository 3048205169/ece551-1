#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int *, size_t);
void test_maxSeq(int array[], size_t n, size_t ans)
{
	size_t ret;

	ret = maxSeq(array, n);
	printf("expect %zu, got %zu\n", ans, ret);
	if (ret != ans) {
		printf("found a bug ! ");
		printf(", n = %zu\n", n);
		exit(EXIT_FAILURE);
	}
}

int main(){
  test_maxSeq((int[]){},0,0);
  test_maxSeq((int[]){1,2,1,2,3},5,3);
  test_maxSeq((int[]){1,1,1},3,1);
  test_maxSeq((int[]){11111111,-222223},2,1);
  test_maxSeq((int[]){1,2,4,6,7},5,5);
}
