#include <iostream>
#include <vector>
#include <seal/seal.h>
#include <cmath>

using namespace std;
using namespace seal;

int main()
{
    // 1️⃣ Tạo tham số mã hóa CKKS
    EncryptionParameters parms(scheme_type::ckks);
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, {60, 40, 40, 60}));

    // 2️⃣ Tạo context
    auto context = SEALContext::Create(parms);
    cout << "SEAL context đã khởi tạo thành công!\n";

    // 3️⃣ Sinh public/secret key
    KeyGenerator keygen(context);
    auto public_key = keygen.public_key();
    auto secret_key = keygen.secret_key();
    auto relin_keys = keygen.relin_keys();
    auto galois_keys = keygen.galois_keys();

    Encryptor encryptor(context, public_key);
    Decryptor decryptor(context, secret_key);
    Evaluator evaluator(context);
    CKKSEncoder encoder(context);

    double scale = pow(2.0, 40);

    // 4️⃣ Dữ liệu đầu vào
    vector<double> input = {3.0, 4.0};
    Plaintext plain;
    encoder.encode(input, scale, plain);

    Ciphertext encrypted;
    encryptor.encrypt(plain, encrypted);

    cout << "Đã mã hóa xong vector {3.0, 4.0}\n";

    // 5️⃣ Cộng 2 lần giá trị mã hóa (tương đương nhân 2)
    Ciphertext encrypted_add;
    evaluator.add(encrypted, encrypted, encrypted_add);

    // 6️⃣ Nhân 2 lần giá trị mã hóa
    Ciphertext encrypted_mul;
    evaluator.multiply(encrypted, encrypted, encrypted_mul);
    evaluator.relinearize_inplace(encrypted_mul, relin_keys);
    evaluator.rescale_to_next_inplace(encrypted_mul);

    // 7️⃣ Giải mã để kiểm tra
    Plaintext plain_add, plain_mul;
    vector<double> decoded_add, decoded_mul;

    decryptor.decrypt(encrypted_add, plain_add);
    decryptor.decrypt(encrypted_mul, plain_mul);

    encoder.decode(plain_add, decoded_add);
    encoder.decode(plain_mul, decoded_mul);

    cout << "\nKết quả cộng (x + x): " << decoded_add[0] << ", " << decoded_add[1] << endl;
    cout << "Kết quả nhân (x * x): " << decoded_mul[0] << ", " << decoded_mul[1] << endl;

    return 0;
}
