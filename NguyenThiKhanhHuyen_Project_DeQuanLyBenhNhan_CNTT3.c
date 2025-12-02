#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
#include <math.h>
#include <stdbool.h> 

#define MAX_PATIENTS 100
#define ID_LEN 20
#define NAME_LEN 50
#define PHONE_LEN 15
#define PATIENTS_PER_PAGE 3 
#define MAX_RECORDS 100

typedef struct {
    char cardId[ID_LEN];
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int visitDays;
    float debt;
} Patient;

typedef struct {
    char recId[ID_LEN]; 
    char cardId[ID_LEN]; 
    char date[NAME_LEN]; 
    char status[NAME_LEN]; 
} Record;

Patient patients[MAX_PATIENTS];
Record records[MAX_RECORDS];
int pCount = 0;
int rCount = 0; 
int totalPatients = 0;


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

bool is_leap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

bool is_valid_date(int day, int month, int year) {
    if (year < 2025 || year > 2030 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (is_leap(year)) {
        days_in_month[2] = 29;
    }

    if (day > days_in_month[month]) {
        return false;
    }

    return true;
}

void parse_date(const char *date_str, int *d, int *m, int *y) {
    sscanf(date_str, "%d/%d/%d", d, m, y);
}

int isCardIdExist(char* id) {
    for(int i = 0; i < totalPatients; i++){
        if(strcmp(patients[i].cardId, id) == 0){
            return 1;
        }
    }
    return 0;
}

int findPatientIndex(char id[]){
    for(int i = 0; i < totalPatients; i++){
        if(strcmp(patients[i].cardId, id) == 0){
            return i;
        }
    }
    return -1;
}

int isValidPhone(char phone[]) {
    int len = strlen(phone);
    
    if(len == 0){
        printf("=> LOI: So dien thoai khong duoc de rong!\n");
        return 0;
    }
    
    if (len < 10 || len > 11) {
        return 0; 
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            return 0; 
        }
    }
    return 1;
}

void initializeData() {
    if (totalPatients == 0) {
        Patient tempPatient; 

        strcpy(tempPatient.cardId, "001");
        strcpy(tempPatient.name, "Nguyen Khanh Huyen");
        strcpy(tempPatient.phone, "0344228207");
        tempPatient.debt = 500000;
        tempPatient.visitDays = 5; 
        patients[totalPatients++] = tempPatient; 

        strcpy(tempPatient.cardId, "002");
        strcpy(tempPatient.name, "Nguyen Nhu Quynh");
        strcpy(tempPatient.phone, "0987654321");
        tempPatient.debt = 1200000;
        tempPatient.visitDays = 20;
        patients[totalPatients++] = tempPatient;

        strcpy(tempPatient.cardId, "003");
        strcpy(tempPatient.name, "Cao Xuan Cuong");
        strcpy(tempPatient.phone, "0312345678");
        tempPatient.debt = 0;
        tempPatient.visitDays = 2;
        patients[totalPatients++] = tempPatient;
        
        strcpy(tempPatient.cardId, "004");
        strcpy(tempPatient.name, "Vu Manh Hung");
        strcpy(tempPatient.phone, "0771234567");
        tempPatient.debt = 350000;
        tempPatient.visitDays = 3;
        patients[totalPatients++] = tempPatient;
        
        strcpy(tempPatient.cardId, "005");
        strcpy(tempPatient.name, "Vu Anh Duc");
        strcpy(tempPatient.phone, "0909090909");
        tempPatient.debt = 2000000;
        tempPatient.visitDays = 1;
        patients[totalPatients++] = tempPatient;
        
        strcpy(tempPatient.cardId, "006");
        strcpy(tempPatient.name, "Vu Quoc Khanh");
        strcpy(tempPatient.phone, "0101010101");
        tempPatient.debt = 1000000;
        tempPatient.visitDays = 4;
        patients[totalPatients++] = tempPatient;
        
        strcpy(tempPatient.cardId, "007");
        strcpy(tempPatient.name, "Ngo Xuan Tai");
        strcpy(tempPatient.phone, "0121212121");
        tempPatient.debt = 3000000;
        tempPatient.visitDays = 5;
        patients[totalPatients++] = tempPatient;
    }
}

void addPatient(){
    if(totalPatients >= MAX_PATIENTS){
        printf("=> LOI: Danh sach benh nhan da day!\n");
        return;
    }
    Patient newPatient;
    printf("\n--- F01: Tiep nhan benh nhan moi ---\n");
    do {
        printf("Nhap cardId: ");
        fgets(newPatient.cardId, sizeof(newPatient.cardId), stdin);
        newPatient.cardId[strcspn(newPatient.cardId, "\n")] = '\0';
        if(strlen(newPatient.cardId) == 0){
            printf("=> LOI: cardId khong duoc rong!\n");
        } else if(isCardIdExist(newPatient.cardId)){
            printf("=> LOI: cardId da ton tai! Vui long nhap lai.\n");
        }
    } while(strlen(newPatient.cardId) == 0 || isCardIdExist(newPatient.cardId));

    do {
        printf("Nhap ten benh nhan: ");
        fgets(newPatient.name, sizeof(newPatient.name), stdin);
        newPatient.name[strcspn(newPatient.name, "\n")] = 0;
        if(strlen(newPatient.name) == 0){
            printf("=> LOI: Ten khong duoc rong!\n");
        }
    } while(strlen(newPatient.name) == 0);

     do {
    printf("Nhap so dien thoai (10-11 so): ");
    fgets(newPatient.phone, sizeof(newPatient.phone), stdin);
    newPatient.phone[strcspn(newPatient.phone, "\n")] = '\0';
    if (!isValidPhone(newPatient.phone)) {
        printf("=> LOI: So dien thoai khong hop le (phai la 10-11 chu so)!\n");
    }
} while(!isValidPhone(newPatient.phone));

   do {
        printf("Nhap debt (cong no > 0): ");
        float tempDebt; 
        if (scanf("%f", &tempDebt) == 1 && tempDebt > 0){ 
            newPatient.debt = tempDebt; 
            clearInputBuffer(); 
            break; 
        } else {
            printf("=> LOI: Cong no phai la mot so duong (> 0)!\n");
            clearInputBuffer(); 
        }
    } while(1);

    newPatient.visitDays = 0;
    patients[totalPatients++] = newPatient;
    printf("=> THONG BAO: Tiep nhan benh nhan thanh cong!\n");
}

void updatePatient(){
    char id[ID_LEN];
	int idx = -1;
    printf("\n--- F02: Cap nhat thong tin benh nhan ---\n");
    do{
        printf("Nhap cardId can cap nhat: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;
        idx = findPatientIndex(id);
        if(idx == -1){
            printf("=> LOI: Khong tim thay benh nhan co cardId: %s! Vui long nhap lai.\n", id);
		}
	}while(idx == -1);
    
    printf("Tim thay benh nhan: %s. Bat dau cap nhat.\n", patients[idx].name);
    printf(">> De trong mot truong va nhan Enter de giu lai gia tri cu.\n");
    char tempInput[NAME_LEN]; 
    int valid = 0;

    printf("Nhap ten moi (Hien tai: %s): ", patients[idx].name);
    fgets(tempInput, sizeof(tempInput), stdin);
    tempInput[strcspn(tempInput, "\n")] = 0;
    if(strlen(tempInput) > 0){
        strcpy(patients[idx].name, tempInput);
    }
    do {
        printf("Nhap so dien thoai moi (10-11 so, Hien tai: %s): ", patients[idx].phone);
        fgets(tempInput, sizeof(tempInput), stdin);
        tempInput[strcspn(tempInput, "\n")] = 0;
        valid = 1;
        if(strlen(tempInput) > 0){
            if(!isValidPhone(tempInput)){
                valid = 0; 
            } else {
                strcpy(patients[idx].phone, tempInput);
            }
        }
    } while(!valid);
    printf("=> THONG BAO: Cap nhat thong tin thanh cong!\n");
}

void recordNewVisit() {
    if (rCount >= MAX_RECORDS) {
        printf("Bo nho Record day!\n");
        return;
    }

    char id[ID_LEN], date[NAME_LEN], status[NAME_LEN];
    printf("\n--- F07: GHI NHAN KHAM BENH ---\n");
    printf("Nhap cardId benh nhan: ");
    fgets(id, sizeof(id), stdin); 
	removeNewline(id);

    int idx = findPatientIndex(id);
    if (idx == -1) {
        printf("Loi: cardId khong ton tai.\n");
        return;
    }

    int day, month, year;
    bool dateValid = false;

    do {
        printf("Nhap Ngay kham (dd/mm/yyyy): ");
        fgets(date, sizeof(date), stdin); 
        removeNewline(date);

        parse_date(date, &day, &month, &year);

        if (is_valid_date(day, month, year)) {
            dateValid = true;
        } else {
            printf("=> LOI: Ngay thang nam khong hop le (%s). Vui long nhap lai.\n", date);
        }
    } while (!dateValid);

    Record r;
    sprintf(r.recId, "REC%03d", rCount + 1);
    strcpy(r.cardId, id);
    strcpy(r.date, date); 

    printf("Nhap trang thai (Tai kham/Theo doi...): ");
    fgets(status, sizeof(status), stdin); removeNewline(status);
    strcpy(r.status, status);

    records[rCount++] = r;
    patients[idx].visitDays++; 
    patients[idx].debt += 100000; 
    printf("Ghi nhan kham benh thanh cong! (recId: %s, Cong no moi: %.f VND)\n", r.recId, patients[idx].debt);
}

void dischargePatient() {
    char id[ID_LEN];
    printf("\n--- F03: Xuat Vien (Xoa Benh Nhan) ---\n");
    printf("Nhap cardId cua benh nhan can xuat vien: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    int idx = findPatientIndex(id);
    if (idx == -1) {
        printf("=> LOI: Khong tim thay benh nhan can xoa.\n");
        return;
    }
	printf("---Xuat vien cho BN: %s (CardID: %s)---\n", patients[idx].name, patients[idx].cardId);
    if (fabs(patients[idx].debt) > 0.001) {
        char confirm;
        printf("=> CANH BAO! Benh nhan %s van con cong no chua thanh toan: %.f VND\n", patients[idx].name, patients[idx].debt);
        printf("Benh nhan da thuc hien thanh toan (Y/N): ");
        scanf("%c", &confirm);
        clearInputBuffer();
        if (tolower(confirm) != 'y') {
            printf("=> THONG BAO: Benh nhan can thanh toan het cong no moi co the xuat vien !!\n");
            return;
    	}
    }
    char confirm_delete;
    printf("Ban co chac chan muon xoa benh nhan nay khong? (Y/N): ");
    scanf("%c", &confirm_delete);
    clearInputBuffer();

    if (tolower(confirm_delete) != 'y') {
        printf("=> THONG BAO: Da huy thao tac xoa.\n");
        return;
    }

    for (int i = idx; i < totalPatients - 1; i++) {
        patients[i] = patients[i + 1];
    }
    totalPatients--; 
    printf("\n=> THONG BAO: Da xoa benh nhan ra khoi danh sach.\n");
}

void displayPaginatedPatients(int pageNum) {
    int startIdx = (pageNum - 1) * PATIENTS_PER_PAGE;
    int endIdx = startIdx + PATIENTS_PER_PAGE;
    if (startIdx >= totalPatients) {
        return;
    }
    printf("\n=========================== DANH SACH BENH NHAN (Trang %d) ============================\n", pageNum);
    printf("| %-13s | %-20s | %-15s | %-10s | %-8s |\n",
           "ID/CCCD", "Ho Ten", "Dien Thoai", "Cong No", "So Lan Kham ");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = startIdx; i < endIdx && i < totalPatients; i++) {
        printf("| %-13s | %-20s | %-15s | %-10.f | %-8d     |\n",
               patients[i].cardId,
               patients[i].name,
               patients[i].phone,
               patients[i].debt,
               patients[i].visitDays);
        printf("--------------------------------------------------------------------------------------\n");    
    }
}

void displayAllPatients() {
    if (totalPatients == 0){
        printf("\n=> Chua co benh nhan nao trong danh sach.\n");
        return;
    }

    int currentPage = 1;
    int totalPages = (totalPatients + PATIENTS_PER_PAGE - 1) / PATIENTS_PER_PAGE;
    char choice;
    
    if (totalPages == 0) totalPages = 1;

    while(1) {          
        displayPaginatedPatients(currentPage);
        printf("\nTrang %d/%d. Tuy chon: [T]iep theo, [Q]uay lai, [C]hoose page, [M]enu chinh: ", currentPage, totalPages);
        scanf(" %c", &choice);
        clearInputBuffer();
        choice = tolower(choice);

        if (choice == 't') {
            if (currentPage < totalPages) {
                currentPage++;
            } else {
                printf("=> CANH BAO: Da la trang cuoi cung.\n");
            }
        } else if (choice == 'q') {
            if (currentPage > 1) {
                currentPage--;
            } else {
                printf("=> CANH BAO: Da la trang dau tien.\n");
            }
        } else if (choice == 'c') {
            int page;
            printf("Nhap so trang muon den (1-%d): ", totalPages);
            if (scanf("%d", &page) == 1 && page >= 1 && page <= totalPages) { 
                currentPage = page;
            } else {
                printf("=> LOI: So trang khong hop le hoac nhap sai dinh dang.\n");
            }
            clearInputBuffer();
        } else if (choice == 'm') {
            break;
        } else {
            printf("=> LOI: Lua chon khong hop le. Vui long chon T, Q, C, hoac M.\n");
        }
    }
}

void searchPatientByName() {
    char nameQuery[NAME_LEN];
    int found = 0;
    printf("\n--- F05: Tim Kiem Benh Nhan Theo Ten ---\n");
    printf("Nhap ten hoac mot phan ten can tim: ");
    fgets(nameQuery, sizeof(nameQuery), stdin);
    nameQuery[strcspn(nameQuery, "\n")] = 0;

    if (strlen(nameQuery) == 0) {
        printf("=> LOI: Ten tim kiem khong duoc de trong.\n");
        return;
    }
    
    for(int i = 0; i < strlen(nameQuery); i++) {
        nameQuery[i] = tolower((unsigned char)nameQuery[i]);
    }

    printf("\n================================== Ket qua tim kiem ==================================\n");
    printf("| %-13s | %-20s | %-15s | %-10s | %-8s |\n",
           "ID/CCCD", "Ho Ten", "Dien Thoai", "Cong No", "So Lan Kham ");
    printf("--------------------------------------------------------------------------------------\n");

    for (int i = 0; i < totalPatients; i++) {
        char tempName[NAME_LEN];
        strcpy(tempName, patients[i].name);
        for(int j = 0; j < strlen(tempName); j++) {
            tempName[j] = tolower((unsigned char)tempName[j]);
        }
        
        if (strstr(tempName, nameQuery) != NULL) {
            printf("| %-13s | %-20s | %-15s | %-10.f | %-8d     |\n",
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt,
                   patients[i].visitDays);
            found = 1;
            printf("--------------------------------------------------------------------------------------\n");
        }
    }

    if (!found) {
        printf("=> THONG BAO: Khong tim thay benh nhan nao voi ten \"%s\".\n", nameQuery);
    }
}

void sortPatientsByDebt() {
    if (totalPatients == 0) {
        printf("Danh sach trong.\n");
        return;
    }

    int choice;
    printf("\n--- F06: SAP XEP DANH SACH ---\n");
    printf("1. Tang dan theo Cong no (Debt)\n");
    printf("2. Giam dan theo Cong no (Debt)\n");
    printf("Chon: ");

    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Loi: Lua chon khong hop le. Vui long chon 1 hoac 2.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    for (int i = 0; i < totalPatients - 1; i++) {
        for (int j = i + 1; j < totalPatients; j++) {
            bool swapNeeded = false;

            if (choice == 1) {
                if (patients[i].debt > patients[j].debt) {
                    swapNeeded = true;
                }
            } else if (choice == 2) {
                if (patients[i].debt < patients[j].debt) {
                    swapNeeded = true;
                }
            }

            if (swapNeeded) {
                Patient temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
    printf("\n=> THONG BAO: Da sap xep thanh cong danh sach cong no.\n");
    
    displayAllPatients(); 
}

void viewVisitHistory() {
    char id[ID_LEN];
    printf("\n--- F08: Xem Lich Su Kham Benh ---\n");
    printf("Nhap cardId cua benh nhan: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0; 

    int idx = findPatientIndex(id);
    int foundRecords = 0; 

    if (idx == -1) {
        printf("=> LOI: Khong tim thay benh nhan.\n");
        return;
    }
    
     printf("\n+= Thong tin tong hop cho BN: %s (ID: %s) =+\n", patients[idx].name, patients[idx].cardId);
     printf("---------------------------------------------------\n");
     printf("| ID Rec      | Ngay Kham     | Trang Thai        |\n");
     printf("---------------------------------------------------\n");
     

     for (int i = 0 ; i < rCount; i++){

     	if (strcmp(records[i].cardId, id) == 0) {
     		printf("| %-11s | %-13s | %-17s |\n", records[i].recId, records[i].date, records[i].status);
     		foundRecords = 1; 
		 }
	 }
	 
	 printf("---------------------------------------------------\n");
     
	 if(!foundRecords){
	 	printf("| Chua co lich su tai kham cho benh nhan nay.       |\n");
        printf("---------------------------------------------------\n");
	 }
}

int main(){
    int choice;
    
    initializeData();

    while(1){
    	system("cls");
        printf("\n+===================== MENU CHINH =======================+\n");
        printf("| 1. F01: Tiep nhan benh nhan moi                        |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 2. F02: Cap nhat thong tin benh nhan                   |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 3. F03: Xuat vien (Xoa benh nhan)                      |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 4. F04: Hien thi danh sach benh nhan (Phan trang)      |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 5. F05: Tim kiem benh nhan theo ten                    |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 6. F06: Sap xep danh sach theo cong no                 |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 7. F07: Ghi nhan kham benh                             |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 8. F08: Xem lich su kham benh                          |\n");
        printf("|--------------------------------------------------------|\n");
        printf("| 9. Thoat chuong trinh                                  |\n");
        printf("+--------------------------------------------------------+\n");
        printf("Chon chuc nang (1-9): ");
        if (scanf("%d", &choice) != 1) {
            printf("=> LOI: Lua chon khong hop le (phai la so)!\n");
            clearInputBuffer();
            choice = 0; 
        }
        getchar();

        switch(choice){
            case 1:
                addPatient();
                break;
            case 2:
                updatePatient();
                break;
            case 3:
                dischargePatient();
                break;
            case 4:
                displayAllPatients(); 
                break;
            case 5:
                searchPatientByName();
                break;
            case 6:
                sortPatientsByDebt(); 
                break;
            case 7:
                recordNewVisit();
                break;
            case 8:
                viewVisitHistory();
                break;
            case 9:
                printf("=> THONG BAO: Tam biet!\n");
                exit(0);
            default:
                printf("=> LOI: Chuc nang khong ton tai. Vui long chon tu 1 den 9.\n");
        }
        
        if (choice != 4 && choice != 6 && choice != 9) {
           printf("\nNhan Enter de tro ve menu chinh...");
           getchar(); 
        }
    }
    return 0;
}

