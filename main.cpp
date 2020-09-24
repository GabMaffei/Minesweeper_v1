#include <iostream>
#include <windows.h> ///para usar as funções Sleep() e system()
#include <time.h> ///para usar a função time
#include <stdlib.h> ///Biblioteca a incluir para gerar números aleatórios
#include <locale.h> ///Texto em português

using namespace std;

#define L 26 ///Número de linhas máximas (máximo do Campo Minado do Windows 10 são 30)(máximo definido como 26, por conta das letras do alfabeto)
#define C 10 ///Número de colunas máximas (máximo do Campo Minado do Windows 10 são 24)(máximo definido como 10, por conta dos dez algarismos)
#define B 259 ///Número de bombas máximas (máximo do Campo Minado do Windows 10 são 667)(máximo definido são 259, pelo limite de bombas em um mapa)

int main()
{
    setlocale(LC_ALL, "Portuguese"); ///Idioma Português
    cout << "CAMPO MINADO em C++" << endl;
    Sleep(300); ///Pausa por x milisegundos
    system("cls"); ///Limpa a tela

    srand(time(NULL)); ///Gerar números aleatórios

    int linhasUsr, colunasUsr, bombasUsr;

    do{ ///Pede o número de linhas e depois colunas e bombas para o usuário, validando a entrada
        cout << "Insira o número de linhas desejado: (padrão = 9)" << endl;
        cin >> linhasUsr;
        if(linhasUsr >= 2 && linhasUsr <= L){
            break;
        } else{
            cout << "Por gentileza, digite um valor entre 2 e " << L << endl;
        }
    } while(true);

    do{
        cout << "Insira o número de colunas desejado: (padrão = 9)" << endl;
        cin >> colunasUsr;
        if(colunasUsr >= 2 && colunasUsr <= C){
            break;
        } else{
            cout << "Por gentileza, digite um valor entre 2 e " << C << endl;
        }
    } while(true);

    do{
        cout << "Insira o número de bombas desejado: (padrão = 10)" << endl;
        cin >> bombasUsr;
        if(bombasUsr >= 2 && bombasUsr <= B && bombasUsr < (colunasUsr * linhasUsr)){
            break;
        } else{
            cout << "Por gentileza, digite um valor entre 2 e " << B << ", e que seja menor do que a área de jogo" << endl;
        }
    } while(true);

    ///system("cls"); ///Limpa a tela

    int mapa[L][C]; ///Legenda: Bombas = -1; Números entre 0 e 8 indicam a quantidade de bombas próximas
    int bx, by, bSucess = 0; ///Para posicionar a bomba; Verificar quantidade

    for(int i = 0; i < L; i++){ ///Limpa o mapa, colocando todas as posições em 0
        for(int j = 0; j < C; j++){
            mapa[i][j] = 0;
        }
    }

    do{ ///Posicionamento das bombas
        if(bSucess == bombasUsr){ ///Caso a quantidade de bombas colocadas já sejam a quantidade pedida, para a repetição
            break;
        }
        bx = rand()%colunasUsr; ///Gera posições aleatórias para a bomba
        by = rand()%linhasUsr;
        ///Comando para exibir geração de bomba, para debugging
        /*cout << "BX = " << bx << endl << "BY = " << by << endl;
        system("pause");*/
        if(mapa[by][bx] != -1){ ///Verifica se não há outra bomba no mesmo local
            mapa[by][bx] = -1; ///Posiciona bomba
            bSucess++; ///Acumula bomba posicionada com sucesso
            for(int i = -1; i <= 1; i++){ ///Adiciona número de bombas próximas
                for(int j = -1; j <= 1; j++){ ///O if verifica se o local é válido, verificando se está dentro do mapa e não tem uma bomba nele
                    if(bx + j >= 0 && by + i >= 0 && mapa[by + i][bx + j] != -1 && bx + j < colunasUsr && by + i < linhasUsr){
                        mapa[by + i][bx + j] = mapa[by + i][bx + j] + 1; ///Adiciona número de quantidade de bombas próximas
                    }
                }
            }
        }
    } while(true);

    bool mapaExibir [L][C], developerMode = false; ///O Primeiro dita os locais já atirados, o segundo verifica se o modo de desenvolvedor está ativo

    for(int i = 0; i < L; i++){ ///Limpa o mapaExibir, colocando todas as posições em false
        for(int j = 0; j < C; j++){
            mapaExibir[i][j] = false;
        }
    }
    ///Comando para exibir a matrix do mapa do campo minado
    /*for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            cout << mapa[i][j] << "  ";
        }
        cout << endl;
    }
    system("pause");*/

    char usrLetra; ///Letra de posição
    bool fim1 = false, fim2 = false; ///Indica final de jogo
    bool entrada; ///Verifica entrada de letra e número de coluna
    int usrLinha, usrColuna; ///Entrada do usuário, com letra já processada
    int jogadasVal = 0; ///Números de jogadas válidas

    do{
        setlocale(LC_ALL, "C"); ///Idioma trocado para padrão, ou "C", para bater com tabela ASCII
        system("cls");
        for(int linha = -1; linha < linhasUsr; linha++){ ///Aqui é feita a renderização do mapa, linha por linha
            if(linha == -1){ ///Na primeira linha, se desenha os números das posições
                cout << "  ";
                for(int i = 0; i < colunasUsr; i++){
                    cout << i;
                }
                cout << endl;
            } else if(linha >= 0){ ///No começo das outras linhas se desenha a letra correspondente a posição
                cout << char(65+linha) << " ";
                for(int coluna = 0; coluna < colunasUsr; coluna++){ ///Depois se desenha o mapa, verificando o está revelado ou não
                    if(mapa[linha][coluna] != -1 && mapaExibir[linha][coluna]){
                        cout << mapa[linha][coluna];
                    } else if(mapa[linha][coluna] != -1 && !(mapaExibir[linha][coluna])){
                        cout << " ";
                    } else if(mapa[linha][coluna] == -1 && mapaExibir[linha][coluna] || developerMode){
                        cout << "*";
                    } else{
                        cout << " ";
                    }
                    }
                }
                cout << endl;
            }
            setlocale(LC_ALL, "Portuguese"); ///Idioma volta a português para textos diversos

            if(fim1){ ///Inicia verificação de fim após o término da impressão do mapa.
                cout << endl << "Parabéns!!! Você ganhou." << endl;
                cout << "Número de jogadas válidas: " << jogadasVal << endl << endl;
                system("pause");
                break;
            }else if(fim2){
                cout << endl << "Ah, não!!! Você acertou uma mina e perdeu." << endl;
                cout << "Número de jogadas válidas: " << jogadasVal << endl << endl;
                system("pause");
                break;
            }

            do{ ///Entrada e validação da letra de posição
                entrada = false;
                cout << "\nEscreva a letra correspondente a linha a ser descoberta: ";
                cin >> usrLetra;
                usrLetra = toupper(usrLetra); ///Transforma letra em maiúscula
                for(int j = 0; j < linhasUsr; j++){ ///Verifica se a letra é válida
                    if(usrLetra == char(65+j)){
                        entrada = true; ///Sendo válida, autoriza parada de entrada
                        break;
                    }else if(usrLetra == '@'){ ///Verifica se a entrada foi o código para o modo de desenvolvedor
                        cout << "Modo de desenvolvedor ligado." << endl;
                        developerMode = true;
                        break;
                    }else if(usrLetra == '*'){ ///Verifica se a entrada foi o código para desabilitar modo de desenvolvedor
                        cout << "Modo de desenvolvedor desligado." << endl;
                        developerMode = false;
                        break;
                    }
                }
                if(entrada){ ///Parada de entrada e validação
                    break;
                }else{ ///Caso não seja uma entrada válida, pede entrada válida e continua repetição
                    cout << "Por favor, digite uma letra válida.";
                }
            } while(true);
            for(int j = 0; j < linhasUsr; j++){ ///Transforma letra em número
                if(usrLetra == char(65+j)){
                    usrLinha = j;
                }
            }
            do{ ///Verificação número coluna
                entrada = false; ///Presume-se que a entrada é falsa e deve se repetir
                cout << "Insira o número da coluna correspondente a ser descoberta: ";
                cin >> usrColuna;
                for(int j = 0; j < colunasUsr; j++){ ///Verifica-se a entrada
                    if(usrColuna == j){
                        entrada = true; ///Entrada verdadeira
                        break;
                    }
                }
                if(!(entrada)){ ///Verifica se a entrada é inválida.
                    cout << "Número inválido." << endl;
                }
            } while(!(entrada)); ///Repetição é parada quando a entrada não for falsa, ou seja verdadeira.
            if(mapa[usrLinha][usrColuna] != -1){
                if(mapaExibir[usrLinha][usrColuna]){
                    cout << "Jogada repetida." << endl;
                    system("pause");
                } else{
                    mapaExibir[usrLinha][usrColuna] = true;
                    jogadasVal++;
                }
            }else{ ///Atingiu uma mina, marca final do jogo
                mapaExibir[usrLinha][usrColuna] = true;
                fim2 = true;
            }

            if((linhasUsr * colunasUsr) - bombasUsr == jogadasVal){ ///Inicia verificação se condição de final de jogo
                fim1 = true; ///Final 1 = Vitória
            }
        ///system("pause");
    } while(true);

    return 0;
}
