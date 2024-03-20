#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Định nghĩa cấu trúc sinh viên
struct Student {
    char hoTen[50];
    char maSV[10];
    float diemToan;
    float diemVan;
    float diemAnhVan;
};

// Mảng lưu trữ danh sách sinh viên
struct Student danhSachSV[MAX_STUDENTS];
int soLuongSV = 0;

// Hàm nhập thông tin của một sinh viên từ bàn phím
void nhapThongTinSinhVien(struct Student *sv) {
    printf("Nhap ho ten: ");
    getchar(); // Xóa ký tự dòng mới từ bộ đệm đầu vào
    fgets(sv->hoTen, sizeof(sv->hoTen), stdin);
    sv->hoTen[strcspn(sv->hoTen, "\n")] = '\0'; // Xóa ký tự dòng mới nếu có
    printf("Nhap ma so sinh vien: ");
    scanf("%s", sv->maSV);
    printf("Nhap diem Toan: ");
    scanf("%f", &sv->diemToan);
    printf("Nhap diem Van: ");
    scanf("%f", &sv->diemVan);
    printf("Nhap diem Anh Van: ");
    scanf("%f", &sv->diemAnhVan);
    getchar(); // Xóa ký tự dòng mới từ bộ đệm đầu vào
}

// Hàm hiển thị thông tin của một sinh viên
void hienThiThongTinSinhVien(struct Student sv) {
    printf("Ho ten: %s\n", sv.hoTen);
    printf("Ma so sinh vien: %s\n", sv.maSV);
    printf("Diem Toan: %.2f\n", sv.diemToan);
    printf("Diem Van: %.2f\n", sv.diemVan);
    printf("Diem Anh Van: %.2f\n", sv.diemAnhVan);
}

// Hàm hiển thị toàn bộ danh sách sinh viên
void hienThiDanhSachSinhVien() {
    if (soLuongSV == 0) {
        printf("Danh sach sinh vien rong.\n");
        return;}
    printf("Danh sach sinh vien:\n");
    for (int i = 0; i < soLuongSV; ++i) {
        printf("===Sinh vien thu %d:===\n", i + 1);
        hienThiThongTinSinhVien(danhSachSV[i]);
        printf("\n");
    }
}

// Hàm tìm kiếm sinh viên theo mã số sinh viên
void timKiemSinhVien(char maSV[]) {
    int found = 0;
    for (int i = 0; i < soLuongSV; ++i) {
        if (strcmp(danhSachSV[i].maSV, maSV) == 0) {
            printf("Thong tin cua sinh vien co ma so %s:\n", maSV);
            hienThiThongTinSinhVien(danhSachSV[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien co ma so %s\n", maSV);
    }
}

// Hàm sửa đổi thông tin của một sinh viên dựa trên Mã số sinh viên
void suaThongTinSinhVien(char maSV[]) {
    for (int i = 0; i < soLuongSV; ++i) {
        if (strcmp(danhSachSV[i].maSV, maSV) == 0) {
            printf("Nhap thong tin moi cho sinh vien:\n");
            nhapThongTinSinhVien(&danhSachSV[i]);
            printf("Da cap nhat thong tin cho sinh vien co ma so %s\n", maSV);
            return;
        }
    }
    printf("Khong tim thay sinh vien co ma so %s\n", maSV);
}

// Hàm xóa thông tin của một sinh viên dựa trên Mã số sinh viên
void xoaSinhVien(char maSV[]) {
    int found = 0;
    for (int i = 0; i < soLuongSV; ++i) {
        if (strcmp(danhSachSV[i].maSV, maSV) == 0) {
            found = 1;
            for (int j = i; j < soLuongSV - 1; ++j) {
                danhSachSV[j] = danhSachSV[j + 1];
            }
            soLuongSV--;
            printf("Da xoa sinh vien co ma so %s\n", maSV);
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien co ma so %s\n", maSV);
    }
}

// Hàm tính điểm trung bình của một sinh viên
float tinhDiemTrungBinh(struct Student sv) {
    return (sv.diemToan + sv.diemVan + sv.diemAnhVan) / 3.0;
}

// Hàm tính điểm trung bình của toàn bộ danh sách sinh viên
float tinhDiemTrungBinhDanhSach() {
    float tongDiem = 0;
    for (int i = 0; i < soLuongSV; ++i) {
        tongDiem += tinhDiemTrungBinh(danhSachSV[i]);
    }
    return tongDiem / soLuongSV;
}

// Hàm lưu danh sách sinh viên vào một file văn bản
void luuDanhSachSinhVienVaoFile(char *tenFile) {
    FILE *file = fopen(tenFile, "w");
    if (file == NULL) {
        printf("Khong mo duoc file de ghi!\n");
        return;
    }
    fprintf(file, "===Danh sach sinh vien:===\n");
    for (int i = 0; i < soLuongSV; i++) {
        fprintf(file, "-Sinh vien %d:\n", i + 1);
        fprintf(file, "Ho ten: %s\n", danhSachSV[i].hoTen);
        fprintf(file, "Ma so sinh vien: %s\n", danhSachSV[i].maSV);
        fprintf(file, "Diem Toan: %.2f\n", danhSachSV[i].diemToan);
        fprintf(file, "Diem Van: %.2f\n", danhSachSV[i].diemVan);
        fprintf(file, "Diem Anh Van: %.2f\n", danhSachSV[i].diemAnhVan);
    }
    fclose(file);
    printf("Da luu danh sach sinh vien vao file %s\n", tenFile);
}

// Hàm đọc danh sách sinh viên từ một file văn bản
void docDanhSachSinhVienTuFile(char *tenFile) {
    FILE *file = fopen(tenFile, "r");
    if (file == NULL) {
        printf("Khong mo duoc file de doc!\n");
        return;
    }
        while (fscanf(file, "%[^\n]%*c", danhSachSV[soLuongSV].hoTen) != EOF) {
        fscanf(file, "%s\n%f\n%f\n%f\n", danhSachSV[soLuongSV].maSV,
               &danhSachSV[soLuongSV].diemToan,
               &danhSachSV[soLuongSV].diemVan,
               &danhSachSV[soLuongSV].diemAnhVan);
        soLuongSV++;
    } 
    
    fclose(file);
    printf("Da doc danh sach sinh vien tu file %s\n", tenFile);
}
void clearScreen() {
    system("clear"); // On Linux and MacOS
    // system("cls"); // On Windows
}


int main() {
    int choice;
    char maSV[10];
    char tenFile[50];
    char exitChoice;

    do {
        clearScreen();
        printf("\n====== MENU ======\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Tim kiem sinh vien\n");
        printf("4. Sua doi thong tin sinh vien\n");
        printf("5. Xoa sinh vien\n");
        printf("6. Thong ke diem trung binh\n");
        printf("7. Luu danh sach sinh vien vao file (ten file tu nhap)\n");
        printf("8. Doc danh sach sinh vien tu file (ten file tu chon)\n");
        printf("9. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("-Nhap thong tin cho sinh vien moi:\n");
                nhapThongTinSinhVien(&danhSachSV[soLuongSV]);
                soLuongSV++;
                break;
            case 2:
                hienThiDanhSachSinhVien();
                break;
            case 3:
                printf("-Nhap ma so sinh vien can tim: ");
                scanf("%s", maSV);
                timKiemSinhVien(maSV);
                break;
            case 4:
                printf("-Nhap ma so sinh vien can sua: ");
                scanf("%s", maSV);
                suaThongTinSinhVien(maSV);
                break;
            case 5:
                printf("-Nhap ma so sinh vien can xoa: ");
                scanf("%s", maSV);
                xoaSinhVien(maSV);
                break;
            case 6:
                printf("-Diem trung binh cua toan bo danh sach sinh vien: %.2f\n", tinhDiemTrungBinhDanhSach());
                break;
            case 7:
                printf("-Nhap ten file de luu danh sach sinh vien: ");
                scanf("%s", tenFile);
                luuDanhSachSinhVienVaoFile(tenFile);
                break;
            case 8:
                printf("-Nhap ten file de doc danh sach sinh vien: ");
                scanf("%s", tenFile);
                docDanhSachSinhVienTuFile(tenFile);
                break;
            case 9:
                printf("-Ban co chac chan muon thoat? (Y/N): ");
                scanf(" %c", &exitChoice);
                if (exitChoice == 'Y' || exitChoice == 'y') {
                    printf("Tam biet!\n");
                    exit(0);
                }
                break;
            default:
                printf("==Lua chon khong hop le. Vui long chon lai==\n");
        }
        printf("Nhan phim bat ky de tro ve MENU:...");
        getchar(); // Xóa ký tự dòng mới từ bộ đệm đầu vào
        getchar(); // Chờ nhập phím bất kỳ
    } while (1);

    return 0;
}
