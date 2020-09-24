#include <iostream>
#include <windows.h> ///para usar as fun��es Sleep() e system()
#include <time.h> ///para usar a fun��o time
#include <stdlib.h> ///Biblioteca a incluir para gerar n�meros aleat�rios
#include <locale.h> ///Texto em portugu�s

using namespace std;

#define L 26 ///N�mero de linhas m�ximas (m�ximo do Campo Minado do Windows 10 s�o 30)(m�ximo definido como 26, por conta das letras do alfabeto)
#define C 10 ///N�mero de colunas m�ximas (m�ximo do Campo Minado do Windows 10 s�o 24)(m�ximo definido como 10, por conta dos dez algarismos)
#define B 259 ///N�mero de bombas m�ximas (m�ximo do Campo Minado do Windows 10 s�o 667)(m�ximo definido s�o 259, pelo limite de bombas em um mapa)

int main()
{
    setlocale(LC_ALL, "Portuguese"); ///Idioma Portugu�s
    cout << "CAMPO MINADO em C++" << endl;
    Sleep(300); ///Pausa por x milisegundos
    system("cls"); ///Limpa a tela

    srand(time(NULL)); ///Gerar n�meros aleat�rios

    int linhasUsr, colunasUsr, bombasUsr;

    do{ ///Pede o n�mero de linhas e depois colunas e bombas para o usu�rio, validando a entrada
        cout << "Insira o n�mero de linhas desejado: (padr�o = 9)" << endl;
        cin >> linhasUsr;
        if(linhasUsr >= 2 && linhasUsr <= L){
            break;
        } else{
            cout << "Por gentileza, digite um valor entre 2 e " << L << endl;
        }
    } while(true);

    do{
        cout << "Insira o n�mero de colunas desejado: (padr�o = 9)" << endl;
        cin >> colunasUsr;
        if(colunasUsr >= 2 && colunasUsr <= C){
            break;
        } else{
            cout << "Por gentileza, digite um valor entre 2 e " << C << endl;
        }
    } while(true);

    do{
        cout << "Insira o n�mero de bombas desejado: (padr�o = 10)" << endl;
        cin >> bombasUsr;
        if(bombasUsr >= 2 && bombasUsr <= B && bombasUsr < (colunasUsr * linhasUsr)){
            break;
        } else{
            cout << "Por gentileza, digite um valor entre 2 e " << B << ", e que seja menor do que a �rea de jogo" << endl;
        }
    } while(true);

    ///system("cls"); ///Limpa a tela

    int mapa[L][C]; ///Legenda: Bombas = -1; N�meros entre 0 e 8 indicam a quantidade de bombas pr�ximas
    int bx, by, bSucess = 0; ///Para posicionar a bomba; Verificar quantidade

    for(int i = 0; i < L; i++){ ///Limpa o mapa, colocando todas as posi��es em 0
        for(int j = 0; j < C; j++){
            mapa[i][j] = 0;
        }
    }

    do{ ///Posicionamento das bombas
        if(bSucess == bombasUsr){ ///Caso a quantidade de bombas colocadas j� sejam a quantidade pedida, para a repeti��o
            break;
        }
        bx = rand()%colunasUsr; ///Gera posi��es aleat�rias para a bomba
        by = rand()%linhasUsr;
        ///Comando para exibir gera��o de bomba, para debugging
        /*cout << "BX = " << bx << endl << "BY = " << by << endl;
        system("pause");*/
        if(mapa[by][bx] != -1){ ///Verifica se n�o h� outra bomba no mesmo local
            mapa[by][bx] = -1; ///Posiciona bomba
            bSucess++; ///Acumula bomba posicionada com sucesso
            for(int i = -1; i <= 1; i++){ ///Adiciona n�mero de bombas pr�ximas
                for(int j = -1; j <= 1; j++){ ///O if verifica se o local � v�lido, verificando se est� dentro do mapa e n�o tem uma bomba nele
                    if(bx + j >= 0 && by + i >= 0 && mapa[by + i][bx + j] != -1 && bx + j < colunasUsr && by + i < linhasUsr){
                        mapa[by + i][bx + j] = mapa[by + i][bx + j] + 1; ///Adiciona n�mero de quantidade de bombas pr�ximas
                    }
                }
            }
        }
    } while(true);

    bool mapaExibir [L][C], developerMode = false; ///O Primeiro dita os locais j� atirados, o segundo verifica se o modo de desenvolvedor est� ativo

    for(int i = 0; i < L; i++){ ///Limpa o mapaExibir, colocando todas as posi��es em false
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

    char usrLetra; ///Letra de posi��o
    bool fim1 = false, fim2 = false; ///Indica final de jogo
    bool entrada; ///Verifica entrada de letra e n�mero de coluna
    int usrLinha, usrColuna; ///Entrada do usu�rio, com letra j� processada
    int jogadasVal = 0; ///N�meros de jogadas v�lidas

    do{
        setlocale(LC_ALL, "C"); ///Idioma trocado para padr�o, ou "C", para bater com tabela ASCII
        system("cls");
        for(int linha = -1; linha < linhasUsr; linha++){ ///Aqui � feita a renderiza��o do mapa, linha por linha
            if(linha == -1){ ///Na primeira linha, se desenha os n�meros das posi��es
                cout << "  ";
                for(int i = 0; i < colunasUsr; i++){
                    cout << i;
                }
                cout << endl;
            } else if(linha >= 0){ ///No come�o das outras linhas se desenha a letra correspondente a posi��o
                cout << char(65+linha) << " ";
                for(int coluna = 0; coluna < colunasUsr; coluna++){ ///Depois se desenha o mapa, verificando o est� revelado ou n�o
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
            setlocale(LC_ALL, "Portuguese"); ///Idioma volta a portugu�s para textos diversos

            if(fim1){ ///Inicia verifica��o de fim ap�s o t�rmino da impress�o do mapa.
                cout << endl << "Parab�ns!!! Voc� ganhou." << endl;
                cout << "N�mero de jogadas v�lidas: " << jogadasVal << endl << endl;
                system("pause");
                break;
            }else if(fim2){
                cout << endl << "Ah, n�o!!! Voc� acertou uma mina e perdeu." << endl;
                cout << "N�mero de jogadas v�lidas: " << jogadasVal << endl << endl;
                system("pause");
                break;
            }

            do{ ///Entrada e valida��o da letra de posi��o
                entrada = false;
                cout << "\nEscreva a letra correspondente a linha a ser descoberta: ";
                cin >> usrLetra;
                usrLetra = toupper(usrLetra); ///Transforma letra em mai�scula
                for(int j = 0; j < linhasUsr; j++){ ///Verifica se a letra � v�lida
                    if(usrLetra == char(65+j)){
                        entrada = true; ///Sendo v�lida, autoriza parada de entrada
                        break;
                    }else if(usrLetra == '@'){ ///Verifica se a entrada foi o c�digo para o modo de desenvolvedor
                        cout << "Modo de desenvolvedor ligado." << endl;
                        developerMode = true;
                        break;
                    }else if(usrLetra == '*'){ ///Verifica se a entrada foi o c�digo para desabilitar modo de desenvolvedor
                        cout << "Modo de desenvolvedor desligado." << endl;
                        developerMode = false;
                        break;
                    }
                }
                if(entrada){ ///Parada de entrada e valida��o
                    break;
                }else{ ///Caso n�o seja uma entrada v�lida, pede entrada v�lida e continua repeti��o
                    cout << "Por favor, digite uma letra v�lida.";
                }
            } while(true);
            for(int j = 0; j < linhasUsr; j++){ ///Transforma letra em n�mero
                if(usrLetra == char(65+j)){
                    usrLinha = j;
                }
            }
            do{ ///Verifica��o n�mero coluna
                entrada = false; ///Presume-se que a entrada � falsa e deve se repetir
                cout << "Insira o n�mero da coluna correspondente a ser descoberta: ";
                cin >> usrColuna;
                for(int j = 0; j < colunasUsr; j++){ ///Verifica-se a entrada
                    if(usrColuna == j){
                        entrada = true; ///Entrada verdadeira
                        break;
                    }
                }
                if(!(entrada)){ ///Verifica se a entrada � inv�lida.
                    cout << "N�mero inv�lido." << endl;
                }
            } while(!(entrada)); ///Repeti��o � parada quando a entrada n�o for falsa, ou seja verdadeira.
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

            if((linhasUsr * colunasUsr) - bombasUsr == jogadasVal){ ///Inicia verifica��o se condi��o de final de jogo
                fim1 = true; ///Final 1 = Vit�ria
            }
        ///system("pause");
    } while(true);

    return 0;
}
