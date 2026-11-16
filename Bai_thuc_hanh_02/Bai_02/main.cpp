#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    int lay_gio_vao() const;
    int lay_tg_do() const;

    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
int phuong_tien::lay_gio_vao() const { return gio_vao; }
int phuong_tien::lay_tg_do() const { return tg_do; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << " ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int MAX_VEHICLES = 3; 
    phuong_tien ds_xe[MAX_VEHICLES]; 
    int so_luong_xe; 

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const;
    int lay_suc_chua_toi_da() const;
    
    bool kiem_tra_day() const;
    bool them(phuong_tien v);
    int tim_vi_tri_xe(int ma_xe) const;
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    void hien_thi_theo_loai(string loai) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_luong_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_luong_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }

int bai_xe::lay_suc_chua_toi_da() const {
    if (kich_thuoc == 'S') return 1;
    if (kich_thuoc == 'M') return 2;
    return 3; 
}

bool bai_xe::kiem_tra_day() const {
    return so_luong_xe >= lay_suc_chua_toi_da();
}

bool bai_xe::them(phuong_tien v) {
    if (kiem_tra_day()) return false;
    ds_xe[so_luong_xe] = v;
    so_luong_xe++;
    return true;
}

int bai_xe::tim_vi_tri_xe(int ma_xe) const {
    for (int i = 0; i < so_luong_xe; ++i) {
        if (ds_xe[i].lay_ma_xe() == ma_xe) {
            return i;
        }
    }
    return -1;
}

bool bai_xe::xoa(int ma_xe) {
    int idx = tim_vi_tri_xe(ma_xe);
    if (idx == -1) return false;

    for (int j = idx; j < so_luong_xe - 1; ++j) {
        ds_xe[j] = ds_xe[j + 1];
    }
    so_luong_xe--; 
    return true;
}

bool bai_xe::chua(int ma_xe) const {
    return tim_vi_tri_xe(ma_xe) != -1;
}

void bai_xe::hien_thi() const {
    int cap = lay_suc_chua_toi_da();
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_luong_xe << "/" << cap << " xe\n";
    if (so_luong_xe == 0) {
        cout << " (Bai trong)\n";
    } else {
        for (int i = 0; i < so_luong_xe; ++i) {
            ds_xe[i].hien_thi();
        }
    }
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_luong_xe; ++i) {
        if (ds_xe[i].lay_loai_xe() == loai) {
            ++dem; 
            tong += ds_xe[i].tinh_phi();
        }
    }
    return dem > 0;
}

void bai_xe::hien_thi_theo_loai(string loai) const {
    for (int i = 0; i < so_luong_xe; ++i) {
        if (ds_xe[i].lay_loai_xe() == loai) {
            ds_xe[i].hien_thi();
        }
    }
}

class SystemInterface {
private:
    static const int MAX_LOTS = 10; 
    bai_xe ds_bai[MAX_LOTS]; 
    int so_luong_bai; 

public:
    SystemInterface();
    
    bool kiem_tra_ma_bai(int ma) const;
    bool kiem_tra_ma_xe(int ma) const;
    int sinh_ma_ngau_nhien() const;
    
    void runMenu();
};

SystemInterface::SystemInterface() : so_luong_bai(0) {
    srand(static_cast<unsigned int>(time(0)));
}

bool SystemInterface::kiem_tra_ma_bai(int ma) const {
    for (int i = 0; i < so_luong_bai; ++i) {
        if (ds_bai[i].lay_ma() == ma) return true;
    }
    return false;
}

bool SystemInterface::kiem_tra_ma_xe(int ma) const {
    for (int i = 0; i < so_luong_bai; ++i) {
        if (ds_bai[i].chua(ma)) return true;
    }
    return false;
}

int SystemInterface::sinh_ma_ngau_nhien() const {
    return 1000 + rand() % 9000;
}

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
    
        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Loi: Du lieu nhap khong hop le! Vui long nhap lai so tu 1 den 9.\n";
            continue;
        }

        switch (chon) {
            case 1: {
                if (so_luong_bai >= MAX_LOTS) {
                    cout << "Loi: He thong da dat toi da " << MAX_LOTS << " bai do!\n";
                    break;
                }
                int ma; char kt;
                cout << "Ma bai: "; 
                if (!(cin >> ma)) {
                    cin.clear(); cin.ignore(10000, '\n');
                    cout << "Loi nhap lieu!\n"; break;
                }
                cout << "Kich thuoc (S/M/L): "; 
                cin >> kt;

                if (kiem_tra_ma_bai(ma)) {
                    int ma_cu = ma;
                    ma = sinh_ma_ngau_nhien();
                    while (kiem_tra_ma_bai(ma)) ma = sinh_ma_ngau_nhien();
                    cout << "Canh bao: Ma bai " << ma_cu << " da ton tai! Tu dong doi thanh ma ngau nhien: " << ma << "\n";
                }

                ds_bai[so_luong_bai] = bai_xe(ma, kt);
                so_luong_bai++;
                cout << "Da tao bai " << ma << "\n";
                break;
            }
            case 2: {
                if (so_luong_bai == 0) {
                    cout << "Loi: Chua co bai do nao trong he thong!\n";
                    break;
                }
                int ma, gio, tg; string loai;
                cout << "Ma xe: "; 
                if (!(cin >> ma)) {
                    cin.clear(); cin.ignore(10000, '\n');
                    cout << "Loi nhap lieu!\n"; break;
                }
                cout << "Loai (Car/Motorcycle/Bicycle): "; 
                cin >> loai;
                cout << "Gio vao (0-23): "; 
                cin >> gio;
                cout << "Thoi luong (1-23): "; 
                cin >> tg;

                if (kiem_tra_ma_xe(ma)) {
                    int ma_cu = ma;
                    ma = sinh_ma_ngau_nhien();
                    while (kiem_tra_ma_xe(ma)) ma = sinh_ma_ngau_nhien();
                    cout << "Canh bao: Ma xe " << ma_cu << " da ton tai! Tu dong doi thanh ma ngau nhien: " << ma << "\n";
                }

                phuong_tien v(ma, loai, gio, tg);
                bool ok = false;
                
                for (int i = 0; i < so_luong_bai; ++i) {
                    if (!ds_bai[i].kiem_tra_day()) {
                        ds_bai[i].them(v);
                        ok = true;
                        cout << "Da them xe " << ma << " vao bai " << ds_bai[i].lay_ma() 
                             << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
                        break;
                    }
                }
                if (!ok) cout << "Tat ca bai da day!\n";
                break;
            }
            case 3: {
                int ma;
                cout << "Ma bai can xoa: "; 
                if (!(cin >> ma)) {
                    cin.clear(); cin.ignore(10000, '\n');
                    cout << "Loi nhap lieu!\n"; break;
                }

                int vi_tri_bai = -1;
                for (int i = 0; i < so_luong_bai; ++i) {
                    if (ds_bai[i].lay_ma() == ma) {
                        vi_tri_bai = i;
                        break;
                    }
                }

                if (vi_tri_bai == -1) {
                    cout << "Khong tim thay bai do!\n";
                } else {
      
                    for (int j = vi_tri_bai; j < so_luong_bai - 1; ++j) {
                        ds_bai[j] = ds_bai[j + 1];
                    }
                    so_luong_bai--;
                    cout << "Da xoa bai " << ma << "\n";
                }
                break;
            }
            case 4: {
                int ma;
                cout << "Ma xe can lay ra: "; 
                if (!(cin >> ma)) {
                    cin.clear(); cin.ignore(10000, '\n');
                    cout << "Loi nhap lieu!\n"; break;
                }

                bool ok = false;
                for (int i = 0; i < so_luong_bai; ++i) {
                    if (ds_bai[i].xoa(ma)) {
                        ok = true;
                        cout << "Da lay xe ra khoi bai " << ds_bai[i].lay_ma() << "\n";
                        break;
                    }
                }
                cout << (ok ? "" : "Khong tim thay xe\n");
                break;
            }
            case 5: {
                if (so_luong_bai == 0) {
                    cout << "Chua co bai do nao.\n";
                } else {
                    for (int i = 0; i < so_luong_bai; ++i) {
                        ds_bai[i].hien_thi();
                        cout << "--------------------\n";
                    }
                }
                break;
            }
            case 6: {
                int ma;
                cout << "Ma bai: "; 
                if (!(cin >> ma)) {
                    cin.clear(); cin.ignore(10000, '\n');
                    cout << "Loi nhap lieu!\n"; break;
                }

                bool found = false;
                for (int i = 0; i < so_luong_bai; ++i) {
                    if (ds_bai[i].lay_ma() == ma) {
                        ds_bai[i].hien_thi();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay bai do!\n";
                break;
            }
            case 7: {
                string loai;
                cout << "Loai xe: "; cin >> loai;
                
                cout << "\n--- DANH SACH XE THUOC LOAI [" << loai << "] ---\n";
                int tong_so_xe = 0;
                for (int i = 0; i < so_luong_bai; ++i) {
                    int dem; double tong;
                    if (ds_bai[i].co_loai(loai, dem, tong)) {
                        cout << "Bai " << ds_bai[i].lay_ma() << ":\n";
                        ds_bai[i].hien_thi_theo_loai(loai);
                        tong_so_xe += dem;
                    }
                }
                if (tong_so_xe == 0) cout << "Khong co xe nao thuoc loai nay.\n";
                else cout << "Tong so xe loai " << loai << ": " << tong_so_xe << "\n";
                break;
            }
            case 8: {
                string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
                for (int t = 0; t < 3; ++t) {
                    int dem_tong_sys = 0; double tong_phi_sys = 0;
                    cout << "\nLoai: " << loai_arr[t] << "\n";
                    for (int i = 0; i < so_luong_bai; ++i) {
                        int d; double s;
                        if (ds_bai[i].co_loai(loai_arr[t], d, s)) {
                            dem_tong_sys += d;
                            tong_phi_sys += s;
                            cout << " - Bai " << ds_bai[i].lay_ma() << ": " << d << " xe | TB: $" << fixed << setprecision(2) << s / d << "\n";
                        }
                    }
                    if (dem_tong_sys == 0) cout << " => Toan he thong: khong co xe\n";
                    else cout << " => Toan he thong: " << dem_tong_sys << " xe | TB chung: $" << fixed << setprecision(2) << tong_phi_sys / dem_tong_sys << "\n";
                }
                break;
            }
            case 9:
                return;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}


