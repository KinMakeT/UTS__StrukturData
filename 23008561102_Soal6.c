#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define MAX_nomor 20
#define MAX_NAMA 50
#define MAX_ALAMAT 100

typedef struct {
    char nomor[MAX_nomor];
    char nama[MAX_NAMA];
    char alamat[MAX_ALAMAT];
} Pelanggan;

typedef struct pelanggan_baru {
    Pelanggan data;
    struct pelanggan_baru *next;
} pelanggan_baru;

pelanggan_baru *hashTable[TABLE_SIZE];

int hashing(char *nomor)
{
    int hash = 0;
    for (int i = 0; i < strlen(nomor); i++)
    {
        hash = hash + nomor[i];
    }
    return hash % TABLE_SIZE;
}

void addDataPelanggan(Pelanggan *Pelanggan)
{
    int index_hash = hashing(Pelanggan->nomor);

    pelanggan_baru *data_baru = (pelanggan_baru *)malloc(sizeof(pelanggan_baru));
    data_baru->data = *Pelanggan;
    data_baru->next = NULL;

    if (hashTable[index_hash] == NULL)
    {
        hashTable[index_hash] = data_baru;
    }
    else
    {
        data_baru->next = hashTable[index_hash];
        hashTable[index_hash] = data_baru;
    }
}

void deleteData(char *nomor)
{
    int index_hash = hashing(nomor);
    pelanggan_baru **ptr_penghapus = &hashTable[index_hash];

    while (*ptr_penghapus != NULL)
    {
        if (strcmp((*ptr_penghapus)->data.nomor, nomor) == 0)
        {
            pelanggan_baru *temp = *ptr_penghapus;
            *ptr_penghapus = (*ptr_penghapus)->next;
            free(temp);
            printf("Pelanggan dengan nomor telepon %s berhasil dihapus.\n", nomor);
            return;
        }
        ptr_penghapus = &(*ptr_penghapus)->next;
    }

    printf("Pelanggan dengan nomor telepon %s tidak ditemukan.\n", nomor);
}

void displayData()
{
    printf("\n+----------------------------+\n");
    printf("| Daftar Pelanggan di Telkom |\n");
    printf("+----------------------------+\n");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        pelanggan_baru *entry = hashTable[i];
        while (entry != NULL)
        {
            printf("Nomor Telepon: %s\nNama: %s\nAlamat: %s\n\n", entry->data.nomor, entry->data.nama, entry->data.alamat);
            entry = entry->next;
        }
    }
}

void addDummy()
{
    Pelanggan dummy1 = {"085123456555", "Prakha", "Jalan Raya Uluwatu No. 69"};
    Pelanggan dummy2 = {"085123456456", "Gilang", "Jalan Taman Griya No. 420"};
    Pelanggan dummy3 = {"085123456357", "Korneus", "Jalan Gunung Salak No. 39"};

    addDataPelanggan(&dummy1);
    addDataPelanggan(&dummy2);
    addDataPelanggan(&dummy3);

    printf("Data dummy berhasil ditambahkan.\nSecara default ada 3 data dummy yang bercollision\n");
}

int main()
{
    while (1)
    {
        system("cls");
        printf("+-----------------------------------------+\n");
        printf("|                                         |\n");
        printf("| Program Mapping Nomor Telepon di Telkom |\n");
        printf("|                                         |\n");
        printf("+-----------------------------------------+\n");
        printf("Pilihan Menu:\n");
        printf("1. Tampilkan Data Pelanggan\n");
        printf("2. Tambah Data Pelanggan\n");
        printf("3. Hapus Data Pelanggan\n");
        printf("4. Otomatis Tambahkan Data Dummy\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
    
        int pilihan;
        scanf("%d", &pilihan);

        switch (pilihan)
        {
            case 1:
                {
                    int isEmpty = 1;
                    for (int i = 0; i < TABLE_SIZE; i++)
                    {
                        if (hashTable[i] != NULL)
                        {
                            isEmpty = 0;
                            break;
                        }
                    }
                    if (isEmpty)
                    {
                        printf("Tidak ada data yang tersimpan.\n");
                    }
                    else
                    {
                        displayData();
                    }
                    system("pause");
                    break;
                }
                break;
            case 2:
                {
                    Pelanggan pelanggan_baru;
                    printf("Masukkan Nomor Telepon Pelanggan Baru: ");
                    scanf("%s", pelanggan_baru.nomor);
                    printf("Masukkan Nama Pelanggan Baru: ");
                    scanf("%s", pelanggan_baru.nama);
                    printf("Masukkan Alamat Pelanggan Baru: ");
                    scanf("%s", pelanggan_baru.alamat);
                    addDataPelanggan(&pelanggan_baru);
                    printf("Pelanggan berhasil ditambahkan.\n");
                }
                system ("pause");
                break;
            case 3:
                {
                    char nomor[MAX_nomor];
                    printf("Masukkan Nomor Telepon Pelanggan yang Ingin Dihapus: ");
                    scanf("%s", nomor);
                    deleteData(nomor);
                }
                system ("pause");
                break;
            case 4:
                addDummy();
                system ("pause");
                break;
            case 5:
                printf("Program Selesai.\n");
                system ("pause");
                exit(0);
            default:
                printf("Pilihan tidak valid, Silahkan coba lagi\n");
                break;
        }
    }

    return 0;
}