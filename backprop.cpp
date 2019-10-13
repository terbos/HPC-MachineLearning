// Back Propagation Learning Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "patterns.h"


double f(double x) {
	/*
	* --------------------------------------------------
	* ��������� ������������� �������
	* (activation function)
	* --------------------------------------------------
	*/
	double y = tanh(x);
	return y;
}


double fder(double a) {
	/*
	* --------------------------------------------------
	* ��������� ���������� ������������� �������
	* --------------------------------------------------
	*/
	double y = 0.5*(1-a)*(1+a);
	return y;
}


int inputi(char *message) {
	/*
	* --------------------------------------------------
	* Input an integer from keyboard
	* --------------------------------------------------
	*/
	int i;
	printf("%s\n", message);
	scanf("%d", &i);
	return i;
}


double inputd(char *message) {
	/*
	* --------------------------------------------------
	* Input an double from keyboard
	* --------------------------------------------------
	*/
	double d;
	printf("%s\n", message);
	scanf("%lf", &d);
	return d;
}



int main(int argc, char* argv[])
{
	Data data;

	/*
	 * Load pattern data from file: "adult.data"
	 */
	char *Path = "C:\\Users\\Kostas\\Documents\\_work\\Code\\datasets\\UCI\\adult\\";
	char *File = "adult.data";
	char *PathFile = (char *)malloc(strlen(Path) + strlen(File) + 2);
	sprintf(PathFile, "%s%s", Path, File);
	// Read file into daata structure "data"
	input_adult(PathFile, &data);
	printf("pattern dimension:%d\tnumber of patterns:%d\n", data.n, data.N);
	double *x = data.x;
	int *t = data.t;


	/*
	 ************************************************
	 ************************************************
	 * Back-Propagation algorithm
	 ************************************************
	 ************************************************
	 */
	int epoch, pat, layer;
	int i, j;
	
	int MAXEPOCHS = inputi(" Maximum epochs: ");

	// Array J[]: J[epoch] = ���� ����������� ������ ��� ��� ����� "epoch"
	double *J = (double *)malloc( MAXEPOCHS * sizeof(double) );

	double beta = inputd(" Learning rate: ");
	
	int L = inputi(" Number of layers (not counting input layer): ");

	/*
	 * ���������� Array: N[]
	 * N[layer] = ������ �������� ��� ������ layer
	 * layer = 0, ..., L (0=input layer, L=output layer)
	 */
	int *N = (int *)malloc( (L+1) * sizeof(int) );
	N[0] = data.n;

	/*
	 * ���������� Array a[][].
	 * a[layer][i] = ������ ��� ������� i ��� ��������� layer
	 * layer = 0, ..., L (0=input layer, L=output layer)
	 */
	double **a = (double **)malloc( (L+1) * sizeof(double *) );
	a[0] = (double *)malloc( N[0] * sizeof(double *) );
	
	/*
	 * ���������� 3-D Array ����� w[][][].
	 * w[layer][i][j] = �� ��������� ����� ��� ������ �� ������� "i" ��� ��������� "layer" �� �� ������� "j" ��� ��������� "layer-1"
	 * layer = 0, ..., L (0=input layer, L=output layer)
	 * �������� : �� w[0][][] ��� �� ��������������
	 */
	double ***w = (double ***)malloc( (L+1) * sizeof(double **) );

	/*
	 * ���������� 3-D Array updates ����� dw[][][].
	 * dw[layer][i][j] = �� update ��� ������ ��� ������ �� ������� "i" ��� ��������� "layer" �� �� ������� "j" ��� ��������� "layer-1"
	 * layer = 0, ..., L (0=input layer, L=output layer)
	 * �������� : �� dw[0][][] ��� �� ��������������
	 */
	double ***dw = (double ***)malloc( (L+1) * sizeof(double **) );
	
	/*
	 * ���������� 2-D Array ����� delta[][].
	 * delta[layer][i] = �� ����� ��� ������� "i" ��� ��������� "layer"
	 * layer = 0, ..., L (0=input layer, L=output layer)
	 * �������� : �� delta[0][] ��� �� ��������������
	 */
	double **delta = (double **)malloc( (L+1) * sizeof(double *) );

	char *msg = (char *)malloc( 100 * sizeof(char) );

	for (layer = 1; layer <= L; layer++) {
		// N[layer] = ������  �������� ��� ������ "layer"
		if (layer == L) {
			// �� ��������� ������, L, ���� 1 ���� �������
			// ������ �������������� �� dataset "adult"
			N[layer] = 1;
		} else {
			sprintf(msg, " Number of neurons in layer %d: ", layer);
			N[layer] = inputi( msg );
		}

		// ���������� ��� ������ a[layer][]
		a[layer] = (double *)malloc( N[layer] * sizeof(double) );

		// ���������� ��� 2-D ������ w[layer][][]
		w[layer] = (double **)malloc( N[layer] * sizeof(double *) );

		// ���������� ��� 2-D ������ dw[layer][][]
		dw[layer] = (double **)malloc( N[layer] * sizeof(double *) );
		
		// ���������� ��� ������ delta[layer][]
		delta[layer] = (double *)malloc( N[layer] * sizeof(double) );

		// ��� ���� ������� i ��� ��������� layer ������ ��� 1-D ������ w[layer][i][]
		for (i = 0; i < N[layer]; i++) {
			w[layer][i] = (double *)malloc( (N[layer-1]+1) * sizeof(double) );
			dw[layer][i] = (double *)malloc( (N[layer-1]+1) * sizeof(double) );
			// ������������ ��� ����� �� ������� �����
			for (j = 0; j <= N[layer-1]; j++) {
				w[layer][i][j] = 2*(double)rand()/RAND_MAX - 1;
				dw[layer][i][j] = 0;
			}
		}
	}

	double u, MSE;

	for (epoch = 0; epoch < MAXEPOCHS; epoch++) {
		
		/*
		******************************
		* ������������ ��� updates
		******************************
		*/
		for (layer = 1; layer <= L; layer++) {
			for (i = 0; i < N[layer]; i++) {
				dw[ layer ][ i ][ N[layer-1] ] = 0;	// ������
				for (j = 0; j < N[layer-1]; j++) {
					dw[ layer ][ i ][ j ] = 0;
				}
			}
		}

		for (pat = 0; pat < data.N; pat++) {

			/*
			 ******************************
			 * Forward ����
			 ******************************
			 */

			/*
			 * for layer = 0
			 */
			for (i = 0; i < N[0]; i++) {	// for all neurons i of layer 0
				a[0][i] = x[ data.n * pat + i];	// a[0][i] = input i
			}

			/*
			 * for all layers = 1, ..., L
			 */
			for (layer = 1; layer <= L; layer++) {
				for (i = 0; i < N[layer]; i++) {	// for all neurons i of this layer
					u = w[ layer ][ i ][ N[layer-1] ];	// ������
					for (j = 0; j < N[layer-1]; j++) {	// for all neurons j of layer-1
						u += w[layer][i][j] * a[layer-1][j];
					}
					a[layer][i] = f(u);
				}
			}


			/*
			 ******************************
			 * Backward ����
			 ******************************
			 */

			// Layer L has only 1 neuron
			delta[L][0] = fder(a[L][0]) * (t[pat] - a[L][0]);

			// for all layers = L-1, ..., 1
			for (layer = L-1; layer >= 1; layer--) {
				for (i = 0; i < N[layer]; i++) {	// for all neurons i of this layer
					u = 0;
					for (j = 0; j < N[layer+1]; j++) {	// for all neurons j of layer+1
						u += w[layer+1][j][i] * delta[layer+1][j];
					}
					delta[layer][i] = fder(a[layer][i]) * u;
				}
			}

			/*
			 ******************************
			 * ����������� updates
			 ******************************
			 */
			for (layer = 1; layer <= L; layer++) {
				for (i = 0; i < N[layer]; i++) {
					dw[ layer ][ i ][ N[layer-1] ] += beta * delta[layer][i];
					for (j = 0; j < N[layer-1]; j++) {
						dw[ layer ][ i ][ j ] += beta * delta[layer][i] * a[layer-1][j];
					}
				}
			}


		}	// for pat

		/*
		******************************
		* ���� Update
		******************************
		*/
		for (layer = 1; layer <= L; layer++) {
			for (i = 0; i < N[layer]; i++) {
				w[ layer ][ i ][ N[layer-1] ] += dw[ layer ][ i ][ N[layer-1] ];	// ������

				//printf("dw[%d][%d][%d]=%f ", layer,i,N[layer-1],dw[layer][i][N[layer-1]] );

				for (j = 0; j < N[layer-1]; j++) {
					w[ layer ][ i ][ j ] += dw[ layer ][ i ][ j ];

					//printf("dw[%d][%d][%d]=%f ", layer,i,j,dw[layer][i][j] );

				}

				//printf("\n");

			}

			//printf("\n");

		}

		/*
		******************************
		* ����������� ���������
		******************************
		*/
		MSE = 0;	// ������������ ����� ������������ ��������� (Mean Squared Error) = 0

		for (pat = 0; pat < data.N; pat++) {

			/*
			 ******************************
			 * Forward ���� ����
			 ******************************
			 */

			/*
			 * for layer = 0
			 */
			for (i = 0; i < N[0]; i++) {	// for all neurons i of layer 0
				a[0][i] = x[ data.n * pat + i];	// a[0][i] = input i
			}

			/*
			 * for all layers = 1, ..., L
			 */
			for (layer = 1; layer <= L; layer++) {
				for (i = 0; i < N[layer]; i++) {	// for all neurons i of this layer
					u = w[ layer ][ i ][ N[layer-1] ];	// ������
					for (j = 0; j < N[layer-1]; j++) {	// for all neurons j of layer-1
						u += w[layer][i][j] * a[layer-1][j];
					}
					a[layer][i] = f(u);
				}
			}

			// ���������� ���������
			MSE += (t[pat] - a[L][0])*(t[pat] - a[L][0]);

		}

		J[epoch] = MSE / data.N;	// ����� ����

		printf(" ** Epoch %d: MSE = %0.6f\n", epoch, J[epoch] );


	}	// for epoch

	return 0;
}

