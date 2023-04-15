#include <iostream>
#include <dlfcn.h>

typedef int (*Composant1Func)(int, int);
typedef int (*Composant2Func)(int, int);

int main(int argc, char** argv) {
    int data1 = 3;
    int data2 = 5;
    int valeur1;
    int valeur2;

    void* handle1;
    void* handle2;
    Composant1Func composant1;
    Composant2Func composant2;

    // Ouvrir la bibliothèque libComposant1.so
    handle1 = dlopen("/home/anamshaikhyunus/lib_partageable_2023/lib/libComposant1.so", RTLD_LAZY);
    if (!handle1) {
        std::cerr << "Erreur lors de l'ouverture de libComposant1.so : " << dlerror() << std::endl;
        return 1;
    }

    // Résoudre le symbole 'composant1'
    composant1 = (Composant1Func)dlsym(handle1, "composant1");
    if (!composant1) {
        std::cerr << "Erreur lors de la résolution du symbole composant1 : " << dlerror() << std::endl;
        dlclose(handle1);
        return 1;
    }

    // Ouvrir la bibliothèque libComposant2.so
    handle2 = dlopen("/home/anamshaikhyunus/lib_partageable_2023/lib/libComposant2.so", RTLD_LAZY);
    if (!handle2) {
        std::cerr << "Erreur lors de l'ouverture de libComposant2.so : " << dlerror() << std::endl;
        dlclose(handle1);
        return 1;
    }

    // Résoudre le symbole 'composant2'
    composant2 = (Composant2Func)dlsym(handle2, "composant2");
    if (!composant2) {
        std::cerr << "Erreur lors de la résolution du symbole composant2 : " << dlerror() << std::endl;
        dlclose(handle1);
        dlclose(handle2);
        return 1;
    }

    // Appeler les fonctions à partir des bibliothèques chargées
    valeur1 = composant1(data1, data2);
    valeur2 = composant2(data1, data2);

    std::cout << "valeur 1 : " << valeur1 << " valeur 2 : " << valeur2 << std::endl;

    // Fermer les bibliothèques
    dlclose(handle1);
    dlclose(handle2);

    return 0;
}

