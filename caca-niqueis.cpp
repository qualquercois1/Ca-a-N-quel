#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <unistd.h>
#include <cstdlib> 

using namespace std;

class Maquina {
    private:
        vector<string> simbolos;
        vector<string> simbolos_escolhidos;
        int qntd_simbolos;
        double valor_aposta;
        double dinheiro = 500.0;
        double banca = 500.0;
        int iterador = 0;

    public:
        
        void gerarSimbolos() {
            simbolos.push_back(u8"💀");
            simbolos.push_back(u8"🤡");
            simbolos.push_back(u8"👽");
            simbolos.push_back(u8"😺");
            simbolos.push_back(u8"😈");
            //caso precise coloque qntd_simbolos = simbolos.size()
        }
        void aposta() {
            random_device rd; 
            mt19937 gen(rd()); 
            uniform_int_distribution<> distrib(10, 100);

            valor_aposta = double(distrib(gen));
            if(dinheiro-valor_aposta <= 0) {
                valor_aposta = dinheiro;
            }

        }

        void limpar_escolhidos(){
            if(!simbolos_escolhidos.size())return;
            simbolos_escolhidos.pop_back();
            simbolos_escolhidos.pop_back();
            simbolos_escolhidos.pop_back();
        }
        
        void escolher_simbolos() {
            limpar_escolhidos();
            random_device rd; 
            mt19937 gen(rd()); 
            uniform_int_distribution<> distrib(0, 4);
            int v1, v2, v3;
            v1 = distrib(gen);
            v2 = distrib(gen);
            v3 = distrib(gen);
            simbolos_escolhidos.push_back(simbolos[v1]);
            simbolos_escolhidos.push_back(simbolos[v2]);
            simbolos_escolhidos.push_back(simbolos[v3]);
        }
        void mostrar_dinheiro() {
            cout << "Dinheiro: R$ " << dinheiro << "\t\t\t\t\t" << "Banca: R$ " << banca << endl;
        }
        void mostrar_aposta() {
            cout << "Aposta: R$ " << valor_aposta << endl;
        }
        void mostrar_resultado() {
            cout << "\t\t\t\t";
            for(auto a : simbolos_escolhidos) {
                sleep(1);
                cout << a << " " << flush;
            }
            cout << endl;
        }
        void resultado() {
            if(simbolos_escolhidos[0]==simbolos_escolhidos[1]&&simbolos_escolhidos[1]==simbolos_escolhidos[2]){
                double valor = valor_aposta*25;
                sleep(1);
                cout << "Ganhou" << endl;
                if(banca-valor<= 0) {
                    dinheiro += banca;
                    banca = 0;
                } else {
                    dinheiro += valor;
                    banca -= valor;
                }
                if(banca <= 0) {
                    cout << "BANCA FALIU!!!" << endl;
                    cout << "Banca: R$ " << banca << endl;
                    cout << "Dinheiro: R$ " << dinheiro << endl;
                    quick_exit(1);
                }
            } else {
                sleep(1);
                cout << "Perdeu" << endl;
                banca += valor_aposta;
                if(dinheiro-valor_aposta<=0) {
                    dinheiro = 0;
                } else {
                    dinheiro -= valor_aposta;
                }
            }
        }


        void jogar() {
            system("clear");
            cout << iterador++ << endl;
            if(dinheiro <= 0) {
                cout << "SEU DINHEIRO ACABOU!!!" << endl;
                cout << "Banca: R$ " << banca << endl;
                cout << "Dinheiro: R$ " << dinheiro << endl;
                quick_exit(1);
            }
            mostrar_dinheiro();
            aposta();
            mostrar_aposta();
            escolher_simbolos();
            mostrar_resultado();
            resultado();
            sleep(1);
        }

};

int main() {

    Maquina caca_niqueis;
    caca_niqueis.gerarSimbolos();
    while(1) caca_niqueis.jogar();
    return 0;
}