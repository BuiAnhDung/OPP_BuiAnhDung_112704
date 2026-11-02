#include <iostream>
#include <string>

using namespace std;

class Xe {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;
    bool dangChiemCho;

public:
    Xe() {
        maXe = 0;
        loaiXe = "";
        gioVao = 0;
        thoiGianDo = 0;
        phiDoXe = 0.0;
        dangChiemCho = false;
    }

    Xe(int ma, string loai, int gio, int thoiLuong) {
        maXe = ma;
        loaiXe = loai;
        gioVao = gio;
        thoiGianDo = thoiLuong;
        phiDoXe = 0.0;
        dangChiemCho = true;
    }

    int layMaXe() {
        return maXe;
    }
    void ganMaXe(int ma) {
        maXe = ma;
    }

    string layLoaiXe() {
        return loaiXe;
    }
    void ganLoaiXe(string loai) {
        loaiXe = loai;
    }

    int layGioVao() {
        return gioVao;
    }
    void ganGioVao(int gio) {
        gioVao = gio;
    }

    int layThoiGianDo() {
        return thoiGianDo;
    }
    void ganThoiLuongDo(int thoiLuong) {
        thoiGianDo = thoiLuong;
    }

    double layPhiDoXe() {
        return phiDoXe;
    }
    void ganPhiDoXe(double phi) {
        phiDoXe = phi;
    }

    bool layDangChiemCho() {
        return dangChiemCho;
    }
    void ganDangChiemCho(bool trangThai) {
        dangChiemCho = trangThai;
    }

    void hienThi() {
        if (dangChiemCho == true) {
            cout << "Ma xe: " << maXe << " - Loai xe: " << loaiXe << endl;
        
        }
    }
};

class BaiDoXe {
private:
    int maBai;
    char kichThuoc;
    Xe xe1;
    Xe xe2;
    Xe xe3;
    bool coXe1;
    bool coXe2;
    bool coXe3;
    bool daTaoBai;

public:
    BaiDoXe() {
        maBai = 0;
        kichThuoc = 'S';
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;
        daTaoBai = false;
    }
    BaiDoXe(int ma, char kt) {
        maBai = ma;
        kichThuoc = kt;
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;
        daTaoBai = true;
    }
    int layMaBai() { return maBai; }
    void ganMaBai(int ma) { maBai = ma; }
    char layKichThuoc() { return kichThuoc; }
    void ganKichThuoc(char kt) { kichThuoc = kt; }
    bool layDaTaoBai() { return daTaoBai; }
    void ganDaTaoBai(bool b) { daTaoBai = b; }
    bool themXe(Xe x) {
        if (kichThuoc == 'S' || kichThuoc == 's') {
            if (coXe1 == false) {
                xe1 = x;
                coXe1 = true;
                return true;
            }
        }
        else if (kichThuoc == 'M' || kichThuoc == 'm') {
            if (coXe1 == false) {
                xe1 = x;
                coXe1 = true;
                return true;
            }
            else if (coXe2 == false) {
                xe2 = x;
                coXe2 = true;
                return true;
            }
        }
        else if (kichThuoc == 'L' || kichThuoc == 'l') {
            // ...
        }
        return false;
    }
    bool xoaXe(int ma) {
        if (coXe1 == true && xe1.layMaXe() == ma) {
            coXe1 = false;
            return true;
        }
        // ...
        return false;
    }
    void hienThiThongTinBai() {
        if (daTaoBai == true) {
            cout << "Bai do xe ID: " << maBai << " - Size: " << kichThuoc << endl;
            if (coXe1 == true) xe1.hienThi();
            if (coXe2 == true) xe2.hienThi();
            if (coXe3 == true) xe3.hienThi();
        }
    }
};
class GiaoDienHeThong {
private:
    BaiDoXe baiDo1;
    BaiDoXe baiDo2;
    BaiDoXe baiDo3;
    bool coBai1;
    bool coBai2;
    bool coBai3;
public:
    GiaoDienHeThong() {
        coBai1 = false;
        coBai2 = false;
        coBai3 = false;
    }
};
int main() {
    BaiDoXe b1(101, 'M');
    Xe x1(1, "Car", 8, 2);
    
    b1.themXe(x1);
    b1.hienThiThongTinBai();

    return 0;
}
