// Read adult.data
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "patterns.h"


int input_adult( char *DATAFILE, Data *pdata ) {
	/*
	* ------------------------------------------------------------
	* READ THE "ADULT" DATASET FROM A FILE
	* DATAFILE = the file to read
	* ------------------------------------------------------------
	*/
	FILE *fin;
	char field[1000];
	int i, iLine, val;
	int n = 14;		// pattern dimension
	int N = 32561;	// number of patterns

	pdata->n = n;
	pdata->N = N;
	pdata->x = (double *)malloc( N * n * sizeof(double) );
	pdata->t = (int *)malloc( N * sizeof(int) );

	char workclass[8][20] = {"Private", "Self-emp-not-inc", "Self-emp-inc", "Federal-gov", "Local-gov", "State-gov", "Without-pay", "Never-worked"};
	char education[16][20] = {"Bachelors", "Some-college", "11th", "HS-grad", "Prof-school", "Assoc-acdm", "Assoc-voc", "9th", "7th-8th", "12th", "Masters", "1st-4th", "10th", "Doctorate", "5th-6th", "Preschool"};
	char marital_status[7][30] = {"Married-civ-spouse", "Divorced", "Never-married", "Separated", "Widowed", "Married-spouse-absent", "Married-AF-spouse"};
	char occupation[14][20] = {"Tech-support", "Craft-repair", "Other-service", "Sales", "Exec-managerial", "Prof-specialty", "Handlers-cleaners", "Machine-op-inspct", "Adm-clerical", "Farming-fishing", "Transport-moving", "Priv-house-serv", "Protective-serv", "Armed-Forces"};
	char relationship[6][20] = {"Wife", "Own-child", "Husband", "Not-in-family", "Other-relative", "Unmarried"};
	char race[5][20] = {"White", "Asian-Pac-Islander", "Amer-Indian-Eskimo", "Other", "Black"};
	char sex[2][10] = {"Female", "Male"};
	char native_country[41][30] = {"United-States", "Cambodia", "England", "Puerto-Rico", "Canada", "Germany", "Outlying-US(Guam-USVI-etc)", "India", "Japan", "Greece", "South", "China", "Cuba", "Iran", "Honduras", "Philippines", "Italy", "Poland", "Jamaica", "Vietnam", "Mexico", "Portugal", "Ireland", "France", "Dominican-Republic", "Laos", "Ecuador", "Taiwan", "Haiti", "Columbia", "Hungary", "Guatemala", "Nicaragua", "Scotland", "Thailand", "Yugoslavia", "El-Salvador", "Trinadad&Tobago", "Peru", "Hong", "Holand-Netherlands"};
	const int targetoptions = 2;
	char target[targetoptions][10] = {"<=50K", ">50K"};
	int LIM;

	fin = fopen(DATAFILE, "r");
	for (iLine = 0; iLine < N; iLine++) {
		/*
		* READ FILE LINES
		*/
		i = 0;

		//age: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%d", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//workclass: Private, Self-emp-not-inc, Self-emp-inc, Federal-gov, Local-gov, State-gov, Without-pay, Never-worked.
		fscanf(fin, "%[^,], ", field);
		LIM = 8;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &workclass[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		//fnlwgt: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%d", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//education: Bachelors, Some-college, 11th, HS-grad, Prof-school, Assoc-acdm, Assoc-voc, 9th, 7th-8th, 12th, Masters, 1st-4th, 10th, Doctorate, 5th-6th, Preschool.
		fscanf(fin, "%[^,], ", field);
		LIM = 16;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &education[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		//education-num: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%d",  &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//marital-status: Married-civ-spouse, Divorced, Never-married, Separated, Widowed, Married-spouse-absent, Married-AF-spouse.
		fscanf(fin, "%[^,], ", field);
		LIM = 7;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &marital_status[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		//occupation: Tech-support, Craft-repair, Other-service, Sales, Exec-managerial, Prof-specialty, Handlers-cleaners, Machine-op-inspct, Adm-clerical, Farming-fishing, Transport-moving, Priv-house-serv, Protective-serv, Armed-Forces.
		fscanf(fin, "%[^,], ", field);
		LIM = 14;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &occupation[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		//relationship: Wife, Own-child, Husband, Not-in-family, Other-relative, Unmarried.
		fscanf(fin, "%[^,], ", field);
		LIM = 6;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &relationship[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		//race: White, Asian-Pac-Islander, Amer-Indian-Eskimo, Other, Black.
		fscanf(fin, "%[^,], ", field);
		LIM = 5;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &race[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		//sex: Female, Male.
		fscanf(fin, "%[^,], ", field);
		LIM = 2;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &sex[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		//capital-gain: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%d", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//capital-loss: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%d", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//hours-per-week: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%d", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//native-country: United-States, Cambodia, England, Puerto-Rico, Canada, Germany, Outlying-US(Guam-USVI-etc), India, Japan, Greece, South, China, Cuba, Iran, Honduras, Philippines, Italy, Poland, Jamaica, Vietnam, Mexico, Portugal, Ireland, France, Dominican-Republic, Laos, Ecuador, Taiwan, Haiti, Columbia, Hungary, Guatemala, Nicaragua, Scotland, Thailand, Yugoslavia, El-Salvador, Trinadad&Tobago, Peru, Hong, Holand-Netherlands.
		fscanf(fin, "%[^,], ", field);
		LIM = 41;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &native_country[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;


		/*
		* TARGET
		*/
		// < 50k, >=50K
		fscanf(fin, "%[^\n]", field);
		for (val = 0; val < targetoptions; val++) {
			if (strcmp(field, &target[val][0]) == 0) {
				pdata->t[ iLine ] = 2*val - 1;
				break;
			}
		}
		
	}
	fclose(fin);
	return 0;
}



int input_iris( char *DATAFILE, Data *pdata, int class_VS_rest) {
	/*
	* ------------------------------------------------------------
	* READ THE "IRIS" DATASET FROM A FILE
	* DATAFILE = the file to read
	* class_VS_rest = the class to be separated vs. the rest
	* ------------------------------------------------------------
	*/
	if (class_VS_rest < 1 || class_VS_rest > 3) {
		fprintf( stderr, "input_iris: the second argument \"class vs. rest\" should be 1, 2, or 3\n" );
		return -1;
	}

	FILE *fin;
	char field[1000];
	int i, iLine;
	int n =	4;		// pattern dimension
	int N = 150;	// number of patterns
	double val;

	pdata->n = n;
	pdata->N = N;
	pdata->x = (double *)malloc( N * n * sizeof(double) );
	pdata->t = (int *)malloc( N * sizeof(int) );

	const int targetoptions = 3;
	char targetclass[targetoptions][20] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

	fin = fopen(DATAFILE, "r");
	for (iLine = 0; iLine < N; iLine++) {
		/*
		* READ FILE LINES
		*/
		i = 0;

		//   1. sepal length in cm: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%lf", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//   2. sepal width in cm: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%lf", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//   3. petal length in cm: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%lf", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		//   4. petal width in cm: continuous.
		fscanf(fin, "%[^,], ", field);
		sscanf(field, "%lf", &val);
		pdata->x[ iLine * n + i ] = val;
		i++;

		/*
		* TARGET
		*/
		// "Iris-setosa", "Iris-versicolor", "Iris-virginica"
		fscanf(fin, "%[^\n]", field);
		for (int cl = 0; cl < targetoptions; cl++) {
			if (strcmp(field, &targetclass[cl][0]) == 0) {
				if (cl == class_VS_rest - 1 )
					pdata->t[ iLine ] = 1;	// This is the class to be separated
				else
					pdata->t[ iLine ] = -1;	// This is one of the "other" classes
				break;
			}
		}

	}
	fclose(fin);
	return 0;
}




int input_wdbc( char *DATAFILE, Data *pdata) {
	/*
	* --------------------------------------------------------------------------------
	* READ THE "WISCONSIN DIAGNOSTIC BREAST CANCER" (WDBC) DATASET FROM A FILE
	* DATAFILE = the file to read
	* class_VS_rest = the class to be separated vs. the rest
	* --------------------------------------------------------------------------------
	*/
	FILE *fin;
	char field[1000];
	int i, iLine;
	int n =	30;		// pattern dimension
	int N = 569;	// number of patterns
	double val;

	pdata->n = n;
	pdata->N = N;
	pdata->x = (double *)malloc( N * n * sizeof(double) );
	pdata->t = (int *)malloc( N * sizeof(int) );

	const int targetoptions = 2;
	char targetclass[targetoptions][20] = {"B", "M"};

	fin = fopen(DATAFILE, "r");
	for (iLine = 0; iLine < N; iLine++) {
		/*
		* READ FILE LINES
		*/
		
		//	1. ID number (useless)
		fscanf(fin, "%[^,],", field);

		/*
		*	2. TARGET
		*/
		// "B" = benign, "M" = malignant
		fscanf(fin, "%[^,],", field);
		for (int cl = 0; cl < targetoptions; cl++) {
			if (strcmp(field, &targetclass[cl][0]) == 0) {
				pdata->t[ iLine ] = 2*cl - 1;
				break;
			}
		}
		
		//   3-32: 30 real valued features
		//	29 elements terminate with a ","
		for (i = 0; i < 29; i++) {
			fscanf(fin, "%[^,],", field);
			sscanf(field, "%lf", &val);
			pdata->x[ iLine * n + i ] = val;
		}
		//	30-th element terminates with "\n" instead of ","
		fscanf(fin, "%[^\n]", field);
		sscanf(field, "%lf", &val);
		pdata->x[ iLine * n + i ] = val;


	}
	fclose(fin);
	return 0;
}




int input_car( char *DATAFILE, Data *pdata, int class_VS_rest ) {
	/*
	* ------------------------------------------------------------
	* READ THE "CAR" DATASET FROM A FILE
	* DATAFILE = the file to read
	* ------------------------------------------------------------
	*/
	FILE *fin;
	char field[100], *field_clean;
	int i, iLine, val;
	int n = 6;		// pattern dimension
	int N = 1728;	// number of patterns

	pdata->n = n;
	pdata->N = N;
	pdata->x = (double *)malloc( N * n * sizeof(double) );
	pdata->t = (int *)malloc( N * sizeof(int) );

	// buying       v-high, high, med, low
	char buying[4][10] = {"vhigh", "high", "med", "low"};
	// maint        v-high, high, med, low
	char maint[4][10] = {"vhigh", "high", "med", "low"};
	// doors        2, 3, 4, 5more
	char doors[4][10] = {"2", "3", "4", "5more"};
	// persons      2, 4, more
	char persons[3][10] = {"2", "4", "more"};
	// lug_boot     small, med, big
	char lug_boot[3][10] = {"small", "med", "big"};
	// safety       low, med, high
	char safety[3][10] = {"low", "med", "high"};
	// Target:
	// unacc     1210     (70.023 %) 
	// acc        384     (22.222 %) 
	// good        69     ( 3.993 %) 
	// v-good      65     ( 3.762 %) 
	const int targetoptions = 4;
	char targetclass[targetoptions][10] = {"unacc", "acc", "good", "vgood"};
	int LIM;

	fin = fopen(DATAFILE, "r");
	for (iLine = 0; iLine < N; iLine++) {
		/*
		* READ FILE LINES
		*/
		i = 0;

		// 1. buying       vhigh, high, med, low
		fscanf(fin, "%[^,],", field);
		if (field[0] == 10)		// remove any leftover from previous newline
			field_clean = &field[1];
		else
			field_clean = &field[0];
		LIM = 4;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field_clean, &buying[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		// 2. maint        vhigh, high, med, low
		fscanf(fin, "%[^,],", field);
		LIM = 4;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &maint[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		// 3. doors        2, 3, 4, 5more
		fscanf(fin, "%[^,],", field);
		LIM = 4;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &doors[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		// 4. persons      2, 4, more
		fscanf(fin, "%[^,],", field);
		LIM = 3;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &persons[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		// 5. lug_boot     small, med, big
		fscanf(fin, "%[^,],", field);
		LIM = 3;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &lug_boot[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;

		// 6. safety       low, med, high
		fscanf(fin, "%[^,],", field);
		LIM = 3;
		for (val = 0; val < LIM; val++) {
			if (strcmp(field, &safety[val][0]) == 0) {
				pdata->x[ iLine * n + i ] = val + 1;
				break;
			}
		}
		if (val == LIM) {	// Value not found
			pdata->x[ iLine * n + i ] = 0;
		}
		i++;


		/*
		* TARGET
		*/
		// "unacc", "acc", "good", "vgood"
		fscanf(fin, "%[^\n]", field);
		for (int cl = 0; cl < targetoptions; cl++) {
			if (strcmp(field, &targetclass[cl][0]) == 0) {
				if (cl == class_VS_rest - 1 )
					pdata->t[ iLine ] = 1;	// This is the class to be separated
				else
					pdata->t[ iLine ] = -1;	// This is one of the "other" classes
				break;
			}
		}
		
	}
	fclose(fin);
	return 0;
}



