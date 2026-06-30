#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define WHITE   "\033[1;37m"
#define BOLD    "\033[1m"
void addDonor();
void viewDonors();
void updateStock();
void checkAvailability();
void shortagePrediction();
void findNearest();
void checkAppointment();
void bookAppointment();
void viewAppointments();
void clearBuffer() {   // 
    while (getchar() != '\n');
}


  // ----------------STRUCTURES ----------------

typedef struct {
    int id;
    char name[50];
    char blood_group[5];
    char city[30];
    char mobile[11];
} Donor;

typedef struct {
    char hospital[50];
    char city[30];
    char blood_group[5];
    int units;
} Stock;

typedef struct {
    char hospital[50];
    char city[30];
    int distance;
} Hospital;

     // ---------------- LOGIN----------------

#include <stdio.h>
#include <string.h>
#include <conio.h>   // getch()

#include <stdio.h>
#include <string.h>
#include <conio.h>   //  getch()

#define MAX_PASS 20

#include <stdio.h>
#include <string.h>
#include <conio.h>   // getch()

int login() {
    char username[20], password[20];
    char ch;
    int i = 0, role;

    printf(RED "==============================================\n" RESET);
    printf(BOLD GREEN "\n=====   EMERGENCY BLOOD & DONOR SYSTEM =====\n" RESET);
    printf(RED "==============================================\n" RESET);

    //  Role Selection with validation
    while (1) {
        printf("1. Doctor\n");
        printf("2. Leader (Blood Bank Manager)\n");
        printf("3. Finder (Foundation)\n");
        printf("4. Exit Program\n");

        printf("Select Role: ");

        if (scanf("%d", &role) != 1) {
            printf(RED "Invalid input! Enter numbers only.\n" RESET);
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        if (role >= 1 && role <= 4)
            break;

        printf(RED "Invalid choice! Enter 1 to 4 only.\n" RESET);
    }

    //  Exit option
    if (role == 4) {
        printf(GREEN "\nExiting program...\n" RESET);
        return -1;
    }

    //  Username input
    printf(BLUE "Username: " RESET);
    scanf("%s", username);

    //  Password input with masking
    printf(BLUE "Password: " RESET);

    i = 0;
    while (1) {
        ch = getch();

        if (ch == 13)   // Enter key
            break;
        else if (ch == 8) {  // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';

    printf("\n");

    // 🔹 Validation
    if (role == 1 && strcmp(username, "NINAD") == 0 && strcmp(password, "NINAD123") == 0)
        return 1;

    if (role == 2 && strcmp(username, "ALPESH") == 0 && strcmp(password, "ALPESH123") == 0)
        return 2;

    if (role == 3 && strcmp(username, "ASMITA") == 0 && strcmp(password, "ASMITA123") == 0)
        return 3;

    printf(RED "\nInvalid Login!\n" RESET);
    return 0;
}
// ---------------- DONOR CHI MAHITI GHATLI----------------

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ? Structure
typedef struct {
    int id;
    char name[50];
    char blood_group[5];
    char city[30];
    char mobile[11];
}Don;

// ? Blood Group Validation
int isValidBloodGroup(char bg[]) {
    int i;
    char *valid[] = {"A+","A-","B+","B-","O+","O-","AB+","AB-"};
    for(i = 0; i < 8; i++) {
        if(strcmp(bg, valid[i]) == 0)
            return 1;
    }
    return 0;
}

//  Mobile Validation 
int isValidMobile(char mobile[]) {
    int i;
    if(strlen(mobile) != 10)
        return 0;

    if(mobile[0] < '6' || mobile[0] > '9')
        return 0;

    for(i = 0; i < 10; i++) {
        if(!isdigit(mobile[i]))
            return 0;
    }

    return 1;
}

//  Duplicate ID Check
int isDuplicateID(int id) {
    FILE *fp = fopen("donors.txt", "r");
    if(fp == NULL) return 0;

    Don d;

    while(fscanf(fp, "%d|%49[^|]|%4[^|]|%29[^|]|%10[^\n]\n",
                 &d.id, d.name, d.blood_group, d.city, d.mobile) == 5) {
        if(d.id == id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

//  Add Donor Function
void addDonor() {
    FILE *fp = fopen("donors.txt", "a");
    if(fp == NULL){
        printf("File Error!\n");
        return;
    }

    Don d;

    //  ID
    while(1) {
        printf("Enter ID: ");
        if(scanf("%d", &d.id) != 1 || d.id <= 0) {
            printf("Invalid ID!\n");
            while(getchar() != '\n');
        }
        else if(isDuplicateID(d.id)) {
            printf("ID already exists!\n");
        }
        else break;
    }
    while(getchar() != '\n'); // clear buffer

    // ? Name
    while(1) {
        printf("Enter Name: ");
        fgets(d.name, sizeof(d.name), stdin);
        d.name[strcspn(d.name, "\n")] = 0;

        if(strlen(d.name) == 0)
            printf("Name cannot be empty!\n");
        else break;
    }

    //  Blood Group
    while(1) {
        printf("Enter Blood Group: ");
        fgets(d.blood_group, sizeof(d.blood_group), stdin);
        d.blood_group[strcspn(d.blood_group, "\n")] = 0;

        if(!isValidBloodGroup(d.blood_group))
            printf("Invalid Blood Group!\n");
        else break;
    }

    //  City
    while(1) {
        printf("Enter City: ");
        fgets(d.city, sizeof(d.city), stdin);
        d.city[strcspn(d.city, "\n")] = 0;

        if(strlen(d.city) == 0)
            printf("City cannot be empty!\n");
        else break;
    }

    //  Mobile
    while(1) {
        printf("Enter Mobile: ");
        fgets(d.mobile, sizeof(d.mobile), stdin);
        d.mobile[strcspn(d.mobile, "\n")] = 0;

        if(!isValidMobile(d.mobile))
            printf("Invalid Mobile! Must be 10 digits and start with 6-9.\n");
        else break;
    }

    //  Save to file
    fprintf(fp, "%d|%s|%s|%s|%s\n",
            d.id, d.name, d.blood_group, d.city, d.mobile);

    fclose(fp);

    printf("Donor Added Successfully!\n");
}
                              // ---------------- DONORS CHI MAHITI ----------------

void viewDonors() {
    FILE *fp = fopen("donors.txt", "r");
    
    if(fp==NULL){
    	printf("\n\t\tNO Record Found.\n");
    	return;
	}
	Donor d;
	char line[200];

    printf(GREEN "\n--- DONOR LIST ---\n" RESET);
    while(fgets(line,sizeof(line),fp)){
    	char *token = strtok(line," | ");
    	
    	if(token == NULL)continue;
    	d.id= atoi(token);
    	 
    	 token = strtok(NULL,"|");
    	 if(token==NULL)continue;
    	 strcpy(d.name,token);
    	 
    	 token = strtok(NULL,"|");
    	 if(token==NULL)continue;
    	 strcpy(d.blood_group,token);
    	 
    	  token = strtok(NULL,"|");
    	 if(token==NULL)continue;
    	 strcpy(d.city,token);
    	 
    	  token = strtok(NULL,"|");
    	 if(token==NULL)continue;
    	 strcpy(d.mobile,token);
    	 
    	 printf(YELLOW "\nID: %d\n" RESET, d.id);
printf("Name: %s\n", d.name);
printf("Blood Group: %s\n", d.blood_group);
printf("City: %s\n", d.city);
printf("Mobile: %s\n", d.mobile);
printf(CYAN "---------------------------------------\n" RESET);
    }
    fclose(fp);
}
	
    

    // ---------------- UPDATE STOCK ----------------

void updateStock() {
    FILE *fp = fopen("stock.txt", "a");
    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    Stock s;
    getchar(); // clear buffer

    //  Hospital Name
    while(1) {
        printf("Hospital Name: ");
        fgets(s.hospital, sizeof(s.hospital), stdin);
        s.hospital[strcspn(s.hospital, "\n")] = 0;

        if(strlen(s.hospital) == 0)
            printf("Hospital name cannot be empty!\n");
        else break;
    }

    //  City
    while(1) {
        printf("City: ");
        fgets(s.city, sizeof(s.city), stdin);
        s.city[strcspn(s.city, "\n")] = 0;

        if(strlen(s.city) == 0)
            printf("City cannot be empty!\n");
        else break;
    }

    //  Blood Group
    while(1) {
        printf("Blood Group: ");
        fgets(s.blood_group, sizeof(s.blood_group), stdin);
        s.blood_group[strcspn(s.blood_group, "\n")] = 0;

        if(!isValidBloodGroup(s.blood_group))
            printf("Invalid Blood Group!\n");
        else break;
    }

    //  Units Validation (IMPORTANT PART)
    while(1) {
        printf("Units: ");
        if(scanf("%d", &s.units) != 1) {
            printf("Invalid input! Enter numbers only.\n");
            while(getchar() != '\n'); // clear buffer
        }
        else if(s.units <= 0) {
            printf("Units must be greater than 0!\n");
        }
        else if(s.units > 10000) {
            printf("Too large value! Enter realistic units.\n");
        }
        else break;
    }

    // ? Save to file
    fprintf(fp, "%s %s %s %d\n",
            s.hospital, s.city, s.blood_group, s.units);

    fclose(fp);

    printf("Stock Updated Successfully!\n");
}

     // ---------------- CHECK AVAILABILITY ----------------

void checkAvailability() {
    FILE *fp = fopen("stock.txt", "r");
    Stock s;
    char bg[5];

    printf("Enter Blood Group: ");
    scanf("%s", bg);

    int found = 0;
    while (fscanf(fp, "%s %s %s %d",s.hospital, s.city, s.blood_group, &s.units) != EOF) {

        if (strcmp(bg, s.blood_group) == 0 && s.units > 0) {
           printf(GREEN "? Available at %s (%s) Units: %d\n" RESET, s.hospital, s.city, s.units);
            found = 1;
        }

        if (s.units < 5) {
           printf(RED "? ALERT: Shortage in %s for %s\n" RESET, s.city, s.blood_group);
        }
    }

    if (!found)
        printf(RED " Blood Not Available!\n" RESET);

    fclose(fp);
}

                   // ----------------  NEAREST HOSPITAL JAVAL ----------------

void findNearest() {
    FILE *fp = fopen("host.txt", "r");   
    Hospital h;
    char city[30];
    int min = 999, found = 0;
    char nearest[50];

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    printf("Enter Your City: ");
    scanf("%s", city);

    while (fscanf(fp, "%s %s %d", h.hospital, h.city, &h.distance) != EOF) {

        //  ONLY same city check 
        if (strcmp(city, h.city) == 0) {

            if (h.distance < min) {
                min = h.distance;
                strcpy(nearest, h.hospital);
                found = 1;
            }
        }
    }

    if (found)
        printf(GREEN "\nNearest Hospital in %s: %s (Distance: %d km)\n" RESET,
               city, nearest, min);
    else
        printf(RED "No Hospital Found in Your City!\n" RESET);

    fclose(fp);
}

       // ---------------- APPOINTMENT CHECK KAR ----------------

void checkAppointment() {
    printf("Doctor Appointments Available: 10 AM - 4 PM\n");
}
void shortagePrediction() {
    FILE *stockFile = fopen("stock.txt", "r");
    FILE *usageFile = fopen("usage.txt", "r");

    if (stockFile == NULL || usageFile == NULL) {
        printf(RED "File Error! (Check stock.txt / usage.txt)\n" RESET);
        return;
    }

    Stock s;
    char hospital[50], city[30], bg[5];
    int used;

    printf(CYAN "\n========== SHORTAGE PREDICTION REPORT ==========\n" RESET);

    //  Read stock file
    while (fscanf(stockFile, "%s %s %s %d",
                  s.hospital, s.city, s.blood_group, &s.units) == 4) {

        int found = 0;
        float totalUsage = 0;

        rewind(usageFile);  
        // Read usage file
        while (fscanf(usageFile, "%s %s %s %d",
                      hospital, city, bg, &used) == 4) {

            //  match hospital + blood group
            if (strcmp(s.hospital, hospital) == 0 &&
                strcmp(s.blood_group, bg) == 0) {

                totalUsage += used;   // 
                found = 1;
            }
        }

        printf("\n---------------------------------------------\n");
        printf("Hospital: %s | City: %s | Blood: %s\n",
               s.hospital, s.city, s.blood_group);
        printf("Current Stock: %d units\n", s.units);

        if (!found || totalUsage == 0) {
            printf(YELLOW "No usage data available\n" RESET);
            continue;
        }

        
        float avgUsage = totalUsage / 30.0;
        float daysLeft = s.units / avgUsage;

        printf("Avg Daily Usage: %.2f\n", avgUsage);
        printf("Estimated Days Left: %.2f\n", daysLeft);

        // status
        if (daysLeft < 3)
            printf(RED "CRITICAL SHORTAGE!\n" RESET);
        else if (daysLeft < 7)
            printf(YELLOW "Warning: Stock Running Low\n" RESET);
        else
            printf(GREEN "Stock Status: Safe\n" RESET);
    }

    fclose(stockFile);
    fclose(usageFile);
}
#include <stdio.h>
#include <stdlib.h>                                                                                                                                     //atoi
#include <string.h>
#include <ctype.h>

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(char date[]) {
    int d, m, y;

    // Check format DD-MM-YYYY
    if (sscanf(date, "%d-%d-%d", &d, &m, &y) != 3)
        return 0;

    if (y < 1900 || y > 2100)
        return 0;

    if (m < 1 || m > 12)
        return 0;

    if (d < 1)
        return 0;

    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // Leap year check
    if (m == 2 && isLeapYear(y))
        daysInMonth[1] = 29;

    if (d > daysInMonth[m - 1])
        return 0;

    return 1;
}
void bookAppointment() {
    FILE *fp = fopen("appointments.txt", "a");
    if(fp == NULL){
        printf("File Error!\n");
        return;
    }

    char patient[50], hospital[50], date[20], time[10];
    getchar();

    printf("Enter Patient Name: ");
    fgets(patient, sizeof(patient), stdin);
    patient[strcspn(patient, "\n")] = 0;

    printf("Enter Hospital Name: ");
    fgets(hospital, sizeof(hospital), stdin);
    hospital[strcspn(hospital, "\n")] = 0;

    // ? Date Validation Loop
    do {
        printf("Enter Date (DD-MM-YYYY): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = 0;

        if (!isValidDate(date)) {
            printf("Invalid date! Please enter a valid date.\n");
        }

    } while (!isValidDate(date));

    printf("Enter Time (e.g., 11AM): ");
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\n")] = 0;

    fprintf(fp, "%s|%s|%s|%s\n", patient, hospital, date, time);

    fclose(fp);

    printf("Appointment Booked Successfully!\n");
}
void viewAppointments() {
    FILE *fp = fopen("appointments.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    char line[200];

    printf("\n--- APPOINTMENT LIST ---\n");

    while (fgets(line, sizeof(line), fp)) {
    	printf("\n============================================================\n");
        char *patient = strtok(line, "|");
        char *hospital = strtok(NULL, "|");
        char *date = strtok(NULL, "|");
        char *time = strtok(NULL, "|");

        if (patient && hospital && date && time) {
            printf("Patient: %s\nHospital: %s\nDate: %s\nTime: %s\n\n",
                   patient, hospital, date, time);
        }
    }

    fclose(fp);
}
void recordUsage() {

    FILE *fp = fopen("usage.txt", "a");

    if(fp == NULL){
        printf("File Error!\n");
        return;
    }

    char hospital[50], city[30], blood_group[5];
    int units;

    while (getchar() != '\n');  // clear buffer

    //  Hospital Name
    while(1) {
        printf("Enter Hospital Name: ");
        fgets(hospital, sizeof(hospital), stdin);
        hospital[strcspn(hospital, "\n")] = 0;

        if(strlen(hospital) == 0)
            printf("Hospital name cannot be empty!\n");
        else break;
    }

    // City
    while(1) {
        printf("Enter City: ");
        fgets(city, sizeof(city), stdin);
        city[strcspn(city, "\n")] = 0;

        if(strlen(city) == 0)
            printf("City cannot be empty!\n");
        else break;
    }

    //  Blood Group
    while(1) {
        printf("Enter Blood Group: ");
        fgets(blood_group, sizeof(blood_group), stdin);
        blood_group[strcspn(blood_group, "\n")] = 0;

        if(!isValidBloodGroup(blood_group))
            printf("Invalid Blood Group!\n");
        else break;
    }

    //  Units Validation (MAIN FIX)
    while(1) {
        printf("Enter Units Used (Monthly): ");
        
        if(scanf("%d", &units) != 1) {
            printf("Invalid input! Enter numbers only.\n");
            while(getchar() != '\n'); // clear buffer
        }
        else if(units <= 0) {
            printf("Units must be greater than 0!\n");
        }
        else if(units > 10000) {
            printf("Too large value! Enter realistic usage.\n");
        }
        else break;
    }

    //  Save data
    fprintf(fp,"%s %s %s %d\n", hospital, city, blood_group, units);

    fclose(fp);

    printf("Usage Data Stored Successfully!\n");
}
// ---------------- MAIN ----------------

int main() {
    int role;

    while (1) {
        role = login();

        if (role == -1) {
            printf(GREEN "Program Closed Successfully!\n" RESET);
            break;
        }

        // 🔹 DOCTOR MENU
        if (role == 1) {
            int ch;
            do {
                printf(MAGENTA "\n========== DOCTOR MENU ==========\n" RESET);
                printf("1.Check Availability\n");
                printf("2.Find Nearest Hospital\n");
                printf("3.Book Appointment\n");
                printf("4.View Appointment\n");
                printf("5.Check Appointment\n");
                printf("6.Logout\n");
                printf("0.Exit Program\n");

                printf("Enter choice: ");

                if (scanf("%d", &ch) != 1) {
                    printf(RED "Invalid input! Enter numbers only.\n" RESET);
                    while (getchar() != '\n');
                    continue;
                }

                if (ch < 0 || ch > 6) {
                    printf(RED "Invalid choice! Enter 0 to 6 only.\n" RESET);
                    continue;
                }

                switch (ch) {
                    case 1: checkAvailability(); break;
                    case 2: findNearest(); break;
                    case 3: bookAppointment(); break;
                    case 4: viewAppointments(); break;
                    case 5: checkAppointment(); break;
                    case 6: break;  // logout
                    case 0:
                        printf("Exiting Program...\n");
                        exit(0);
                }
            } while (ch != 6);
        }

        //  LEADER MENU
        else if (role == 2) {
            int ch;
            do {
                printf(MAGENTA "\n--- LEADER MENU ---\n" RESET);
                printf("1.Add Donor\n");
                printf("2.View Donor\n");
                printf("3.Update Stock\n");
                printf("4.Record Blood Usage\n");
                printf("5.Logout\n");
                printf("0.Exit Program\n");

                printf("Enter choice: ");

                if (scanf("%d", &ch) != 1) {
                    printf(RED "Invalid input! Enter numbers only.\n" RESET);
                    while (getchar() != '\n');
                    continue;
                }

                if (ch < 0 || ch > 5) {
                    printf(RED "Invalid choice! Enter 0 to 5 only.\n" RESET);
                    continue;
                }

                switch (ch) {
                    case 1: addDonor(); break;
                    case 2: viewDonors(); break;
                    case 3: updateStock(); break;
                    case 4: recordUsage(); break;
                    case 5: break;  // logout
                    case 0:
                        printf("Exiting Program...\n");
                        exit(0);
                }
            } while (ch != 5);
        }

        //  FINDER MENU
        else if (role == 3) {
            int ch;
            do {
                printf(MAGENTA "\n--- FINDER MENU ---\n" RESET);
                printf("1.View All Stock\n");
                printf("2.Shortage Report\n");
                printf("3.Find Nearest Hospital\n");
                printf("4.Logout\n");
                printf("0.Exit Program\n");

                printf("Enter choice: ");

                if (scanf("%d", &ch) != 1) {
                    printf(RED "Invalid input! Enter numbers only.\n" RESET);
                    while (getchar() != '\n');
                    continue;
                }

                if (ch < 0 || ch > 4) {
                    printf(RED "Invalid choice! Enter 0 to 4 only.\n" RESET);
                    continue;
                }

                switch (ch) {
                    case 1: checkAvailability(); break;
                    case 2: shortagePrediction(); break;
                    case 3: findNearest(); break;
                    case 4: break;  // logout
                    case 0:
                        printf("Exiting Program...\n");
                        exit(0);
                }
            } while (ch != 4);
        }
    }

    return 0;
}