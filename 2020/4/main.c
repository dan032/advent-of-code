#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <regex.h>

#define TRUE 1
#define FALSE 0

void problem1(FILE *f);
void problem2(FILE *f);

int main(int argc, char *argv[]){
	char *path = (char*) malloc(100 * sizeof(char));
	sprintf(path, "%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

	problem1(f);
	rewind(f);
	problem2(f);	
	fclose(f);
	

	return 0;
}

void problem1(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	int byr = FALSE, iyr = FALSE, eyr = FALSE, hgt = FALSE;
	int hcl = FALSE, ecl = FALSE, pid = FALSE, cid = FALSE;

	int result = 0;

	regex_t reg_byr, reg_iyr, reg_eyr, reg_hgt;
	regex_t reg_hcl, reg_ecl, reg_pid, reg_cid;

	while((read = getline(&line, &len, f)) != EOF){
		if (strcmp(line, "\n") == 0){
			if (byr && iyr && eyr && hgt && hcl && ecl && pid){
				result++;
			}
			byr = FALSE;
			iyr = FALSE;
			eyr = FALSE;
			hgt = FALSE;
			hcl = FALSE;
			ecl = FALSE;
			pid = FALSE;
			cid = FALSE;
			continue;
		}

		regcomp(&reg_byr, "byr:", 0);
		regcomp(&reg_iyr, "iyr:", 0);
		regcomp(&reg_eyr, "eyr:", 0);
		regcomp(&reg_hgt, "hgt:", 0);
		regcomp(&reg_hcl, "hcl:", 0);
		regcomp(&reg_ecl, "ecl:", 0);
		regcomp(&reg_pid, "pid:", 0);
		regcomp(&reg_cid, "cid:", 0);

		byr = byr ? byr : regexec(&reg_byr, line, 0, NULL, 0) == 0;
		iyr = iyr ? iyr : regexec(&reg_iyr, line, 0, NULL, 0) == 0;
		eyr = eyr ? eyr : regexec(&reg_eyr, line, 0, NULL, 0) == 0;
		hgt = hgt ? hgt : regexec(&reg_hgt, line, 0, NULL, 0) == 0;
		hcl = hcl ? hcl : regexec(&reg_hcl, line, 0, NULL, 0) == 0;
		ecl = ecl ? ecl : regexec(&reg_ecl, line, 0, NULL, 0) == 0;
		pid = pid ? pid : regexec(&reg_pid, line, 0, NULL, 0) == 0;
		cid = cid ? cid : regexec(&reg_cid, line, 0, NULL, 0) == 0;
	}
	printf("%d\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	int byr = FALSE, iyr = FALSE, eyr = FALSE, hgt = FALSE;
	int hcl = FALSE, ecl = FALSE, pid = FALSE, cid = FALSE;

	int result = 0;

	regex_t reg_byr, reg_iyr, reg_eyr, reg_hgt;
	regex_t reg_hcl, reg_ecl, reg_pid, reg_cid;

	while((read = getline(&line, &len, f)) != EOF){
		if (strcmp(line, "\n") == 0){
			if (byr && iyr && eyr && hgt && hcl && ecl && pid){
				result++;
			}
			byr = FALSE;
			iyr = FALSE;
			eyr = FALSE;
			hgt = FALSE;
			hcl = FALSE;
			ecl = FALSE;
			pid = FALSE;
			cid = FALSE;
			continue;
		}

		regcomp(&reg_byr, "byr:[1920-2002]", REG_EXTENDED);
		regcomp(&reg_iyr, "iyr:[2010-2020]", REG_EXTENDED);
		regcomp(&reg_eyr, "eyr:[2020-2030]", REG_EXTENDED);
		regcomp(&reg_hgt, "hgt:([150-193]cm|[59-76]in)", REG_EXTENDED);
		// regcomp(&reg_hcl, "hcl:#([0-9a-f]{6}", REG_EXTENDED);
		// regcomp(&reg_ecl, "ecl:(amb|blu|brn|gry|grn|hzl|oth)", REG_EXTENDED);
		// regcomp(&reg_pid, "pid:[0-9]{9}", REG_EXTENDED);
		// regcomp(&reg_cid, "cid", REG_EXTENDED);

		byr = byr ? byr : regexec(&reg_byr, line, 0, NULL, 0) == 0;
		iyr = iyr ? iyr : regexec(&reg_iyr, line, 0, NULL, 0) == 0;
		eyr = eyr ? eyr : regexec(&reg_eyr, line, 0, NULL, 0) == 0;
		hgt = hgt ? hgt : regexec(&reg_hgt, line, 0, NULL, 0) == 0;
		// hcl = hcl ? hcl : regexec(&reg_hcl, line, 0, NULL, 0) == 0;
		// ecl = ecl ? ecl : regexec(&reg_ecl, line, 0, NULL, 0) == 0;
		// pid = pid ? pid : regexec(&reg_pid, line, 0, NULL, 0) == 0;
		// cid = cid ? cid : regexec(&reg_cid, line, 0, NULL, 0) == 0;
	}
}
