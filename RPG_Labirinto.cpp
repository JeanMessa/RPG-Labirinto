#include<iostream>
#include<string>
#include<list>
#include <cstdlib>
#include<ctime>
#include <locale>
#include<chrono>
#include <thread>
#include <memory>
#include <windows.h>
#include <conio.h>
using namespace std;

class Configuracoes{
	private:
		static int tempo_espera;
	public:
		Configuracoes(int tempo_espera){
			this->tempo_espera = tempo_espera;
		}
		void set_tempo_espera(int tempo){
			this->tempo_espera = tempo;
		}
		static int get_tempo_espera(){
			return tempo_espera;
		} 
};

int Configuracoes::tempo_espera = 0;

class Console{
	private:
		HANDLE handle;
	public:
		Console(){
			handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		void set_cursor(int x = 0 , int y = 0){
		    COORD cordenadas;
		    handle = GetStdHandle(STD_OUTPUT_HANDLE);
		    cordenadas.X = x;
		    cordenadas.Y = y;
		    SetConsoleCursorPosition ( handle , cordenadas );
		}
		void print_color(string texto ,int cor){
		    SetConsoleTextAttribute(handle, cor);
		    cout << texto;
		    SetConsoleTextAttribute(handle, 15);
		}
		void tela_cheia(){
			keybd_event(VK_MENU,0x36,0,0);
			keybd_event(VK_RETURN,0x1C,0,0);
			keybd_event(VK_RETURN,0x1C,KEYEVENTF_KEYUP,0);
			keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
		}
};


const int altura = 15;
const int largura = 15;


class Personagem{
    protected:
        string nome;
        float VID,ATQ,DEF,dano_total_causado,dano_total_sofrido,maior_dano_causado,maior_dano_sofrido;
        list<Personagem*> derrotados;
        string especial,classe;
    public:
    	Personagem(){
    		
		}
        Personagem(string nome){
            this->nome=nome;
            dano_total_causado=0;
			dano_total_sofrido=0;
			maior_dano_causado=0;
			maior_dano_sofrido=0;
        }
        void add_derrotado(Personagem *derrotado){
            derrotados.push_back(derrotado);
        }
        void mostrar(){
            cout << endl << endl << "Nome: " << nome << endl << "Classe: " << classe << endl << "VID: " << VID << endl << "ATQ: " << ATQ << endl << "DEF: " << DEF << endl <<  "Dano Total Causado: " << dano_total_causado << endl <<  "Dano Total Sofrido: " << dano_total_sofrido << endl << "Maior Dano Causado em Um Round: " << maior_dano_causado << endl << "Maior Dano Sofrido em Um Round: " << maior_dano_sofrido << endl << "Derrotados: ";
            for(Personagem* &d :  derrotados){
                cout << endl << d->nome << " - " << d->classe;
            }
        }
        void setnome(string nome){
            this->nome = nome;
        }
        void setVID(float VID){
            this->VID = VID;
        }
        void setATQ(float ATQ){
            this->ATQ = ATQ;
        }
        void setDEF(float DEF){
            this->DEF = DEF;
        }
        string getnome(){
            return nome;
        }
        float getVID(){
            return VID;
        }
        float getATQ(){
            return ATQ;
        }
        float getDEF(){
            return DEF;
        }
        string getClasse(){
            return classe;
        }
        string getEspecial(){
            return especial;
        }
        void soma_dano_total_causado(float dano){
        	dano_total_causado+=dano;
		}
		void soma_dano_total_sofrido(float dano){
        	dano_total_sofrido+=dano;
		}
		void set_maior_dano_causado(float dano){
			if(maior_dano_causado<dano){
				maior_dano_causado=dano;
			}
		}
		void set_maior_dano_sofrido(float dano){
			if(maior_dano_sofrido<dano){
				maior_dano_sofrido=dano;
			}
		}
};

class Arqueiro : public Personagem{
    public:
        Arqueiro(string nome) : Personagem(nome){
            classe = "Arqueiro";
            especial = "Flecha de Espinhos";
            VID = 1400 + (rand() % (1751-1400));
            ATQ = 200 + (rand()% (251-200));
            DEF = 3 + (rand()%(5-3));
        }
};

class Espadachim : public Personagem{
    public:
        Espadachim(string nome) : Personagem(nome){
            classe = "Espadachim";
            especial = "Espadas Duplas";
            VID = 1300 + (rand()%(1601-1300));
            ATQ = 250 + (rand()%(351-250));
            DEF = 2 + (rand()%(4-2));
        }
};

class Curandeiro : public Personagem{
    public:
        Curandeiro(string nome) : Personagem(nome){
            classe = "Curandeiro";
            especial = "Remédios Ancestrais";
            VID = 1800 + (rand()%(2501-1800));
            ATQ = 120 + (rand()%(186-120));
            DEF = 3 + (rand()%(7-3));
        } 
};

class Bombardeiro : public Personagem{
    public:
        Bombardeiro(string nome) : Personagem(nome){
            classe = "Bombardeiro";
            especial = "Kabooom!";
            VID = 1200 + (rand()%(1501-1200));
            ATQ = 200 + (rand()%(401-200));
            DEF = 2 + (rand()%(4-2));
        }
};

class Mago : public Personagem{
    public:
        Mago(string nome) : Personagem(nome){
            classe = "Mago";
            especial = "Balança da Vida";
            VID = 1000 + (rand()%(2001-1000));
            ATQ = 270 + (rand()%(326-270));
            DEF = 2 + (rand()%(6-2));
        }
};

class Mimico : public Personagem{
    public:
        Mimico(string nome) : Personagem(nome){
            classe = "Mímico";
            especial = "Espelho";
            VID = 999 + (rand()%(2002-999));
            ATQ = 119 + (rand()%(402-119));
            DEF = 1+(rand()%(6-1));
        }
};

class JogoRPG{
	public:
		float batalha(Personagem *pontp1, Personagem *pontp2,bool p1_jogador,float vida_atual,int max_turno){
			system("cls");
            cout << endl << endl << "--------------------------------" << endl;
            cout << pontp1->getnome() << " X " << pontp2->getnome()<<endl;
            cout<< "--------------------------------";
            float vidap1;
            float vidap2;
            bool p1_venceu;
            if(p1_jogador){
            	vidap1 = vida_atual;
            	vidap2 = pontp2->getVID();
			}else{
				vidap1 = pontp1->getVID();
            	vidap2 = vida_atual;
			}
            float dano,danop1 = 0, danop2 = 0;
            int r = 1;
            int t=1;
            int duracao_sangramentop1=0,duracao_sangramentop2=0;
            bool sangrou=0;
            int contadorp1 = 0, contadorp2 = 0 ;
            while(vidap1>0 && vidap2>0 && r<=max_turno){
                if(r<=max_turno){
                    if(t%2!=0){//começo do round 
                        cout << endl << endl << "---------------------------ROUND " << r << "---------------------------"<< endl << endl;
                        if(duracao_sangramentop1>0){
                            vidap1-=25;
                            danop2+=25;
                            pontp2->set_maior_dano_causado(25);
                            pontp1->set_maior_dano_sofrido(25);
                            if(vidap1<0){
                                vidap1=0;
                            }
                            cout << pontp1->getnome() << " sangrou e perdeu 25 de vida ficando com " << vidap1 <<endl;
                            duracao_sangramentop1--;
                            sangrou=1;
                        }
                        if(duracao_sangramentop2>0){
                            vidap2-=25;
                            danop1+=25;
                            pontp1->set_maior_dano_causado(25);
                            pontp2->set_maior_dano_sofrido(25);
                            if(vidap2<0){
                                vidap2=0;
                            }
                            cout << pontp2->getnome() << " sangrou e perdeu 25 de vida ficando com " << vidap2 << endl;
                            duracao_sangramentop2--;
                            sangrou=1;
                        }
                        if(sangrou){
                            cout << "--" << endl;
                            sangrou=0;
                        }
                        // ataque do p1
                        if(rand()%4 != 0 && vidap1>0){ //ataque normal
                            dano = (pontp1->getATQ() + (pontp1->getATQ() * (1+rand()%100)/100))/pontp2->getDEF();
                        }else if(vidap1>0){ //ataque especial
                            cout << pontp1->getnome() << " usou " << pontp1->getEspecial()<<endl;
                            if(pontp1->getClasse() == "Arqueiro"){
                                dano = (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
                                 duracao_sangramentop2 += 2 + rand()%5;
                                    cout << "deixando " << pontp2->getnome() << " com " << duracao_sangramentop2 << " turnos de sangramento" << endl;
                            }else if(pontp1->getClasse() == "Espadachim"){
                                dano = (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
                                dano += (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
                                cout << "realizando dois ataques" << endl;
                            }else if(pontp1->getClasse() == "Curandeiro"){
                                dano = 0;
                                int cura;
                                cura = pontp1->getVID() *0.5;
                                if(vidap1 + cura > pontp1->getVID()){
                                    cura = pontp1->getVID() - vidap1;
                                }
                                vidap1 += cura;
                                cout << "curando sua vida em "<< cura << " pontos" << endl;
                            }else if(pontp1->getClasse() == "Bombardeiro"){
                                dano = (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
								pontp1->soma_dano_total_sofrido(dano);
                            	pontp1->set_maior_dano_sofrido(dano);
                                vidap1-=dano;
                                cout << "causando uma explosão e também " << dano << " de dano a si mesmo" << endl;
                                dano *= 3;
                            }else if(pontp1->getClasse() == "Mago"){
                                if(vidap1>=vidap2){
                                    dano = vidap2*0.1;
                                     cout << "fazendo com que seu dano seja 10% da vida do oponente" << endl;
                                }else{
                                    dano = vidap2*0.3;
                                    cout << "fazendo com que seu dano seja 30% da vida do oponente" << endl;
                                }                                
                            }else if(pontp1->getClasse() == "Mímico"){
                                cout << "copiando " << pontp2->getEspecial() << " e" << endl;
                                if(pontp2->getClasse() == "Arqueiro"){
                                    dano = (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
                                    duracao_sangramentop2 += 2 + rand()%5;
                                    cout << "deixando " << pontp2->getnome() << " com " << duracao_sangramentop2 << " turnos de sangramento" << endl;
                                }else if(pontp2->getClasse() == "Espadachim"){
                                    dano = (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
                                    dano += (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
                                    cout << "realizando dois ataques" << endl;
                                }else if(pontp2->getClasse() == "Curandeiro"){
                                    dano = 0;
                                    int cura;
                                    cura = pontp1->getVID() *0.5;
                                    if(vidap1 + cura > pontp1->getVID()){
                                        cura = pontp1->getVID() - vidap1;
                                    }
                                    vidap1 += cura;
                                    cout << "curando sua vida em "<< cura << " pontos" << endl;
                                }else if(pontp2->getClasse() == "Bombardeiro"){
                                    dano = (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
									pontp1->soma_dano_total_sofrido(dano);
                            		pontp1->set_maior_dano_sofrido(dano);
                                    vidap1-=dano;
                                    cout << "causando uma explosão e também " << dano << " de dano a si mesmo" << endl;
                                    dano *= 3;
                                }else if(pontp2->getClasse() == "Mago"){
                                    if(vidap1>=vidap2){
                                        dano = vidap2*0.1;
                                        cout << "fazendo com que seu dano seja 10% da vida do oponente" << endl;
                                    }else{
                                        dano = vidap2*0.3;
                                        cout << "fazendo com que seu dano seja 30% da vida do oponente" << endl;
                                    }                                
                                }else if(pontp2->getClasse() == "Mímico"){
                                    dano = (pontp1->getATQ() + (pontp1->getATQ() * (50+rand()%51)/100))/pontp2->getDEF();
                                    cout << "nada aconteceu" << endl;
                                }
                            }
                            contadorp1 ++;
                        }else{
                            dano = 0;
                        }
                        danop1 += dano;
                        vidap2 -= dano;
                        pontp1->set_maior_dano_causado(dano);
                        pontp2->set_maior_dano_sofrido(dano);
                        if(vidap2>0 && vidap1>0){
                            cout << pontp1->getnome() << " atacou deu " << dano << " de dano, e deixou " << pontp2->getnome() << " com " << vidap2 << " de vida" << endl;
                        }else if(vidap1>0){
                            cout << pontp1->getnome() << " atacou deu " << dano << " de dano, e derrotou " << pontp2->getnome() << endl << endl;     
                        }         
                    }else{ //ataque do p2
                        cout<< "--" << endl;
                        if(rand()%4 != 0){  //ataque normal
                            dano = (pontp2->getATQ() +(pontp2->getATQ() * (1+rand()%100)/100))/pontp1->getDEF();
                        }else{ //ataque especial
                            cout << pontp2->getnome() << " usou " << pontp2->getEspecial()<<endl;
                            if(pontp2->getClasse() == "Arqueiro"){
                                dano = (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                duracao_sangramentop1 += 2 + rand()%5;
                                cout << "deixando " << pontp1->getnome() << " com " << duracao_sangramentop1 << " turnos de sangramento" << endl;
                            }else if(pontp2->getClasse() == "Espadachim"){
                                dano = (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                dano += (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                cout << "realizando dois ataques" << endl;
                            }else if(pontp2->getClasse() == "Curandeiro"){
                                dano = 0;
                                int cura;
                                cura = pontp2->getVID() *0.5;
                                if(vidap2 + cura > pontp2->getVID()){
                                    cura = pontp2->getVID() - vidap2;

                                }
                                vidap2 += cura;
                                cout << "curando sua vida em "<< cura << " pontos" << endl;
                            }else if(pontp2->getClasse() == "Bombardeiro"){
                                dano = (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                pontp2->soma_dano_total_sofrido(dano);
                            	pontp2->set_maior_dano_sofrido(dano);
                                vidap2-=dano;
                                cout << "causando uma explosão e também " << dano << " de dano a si mesmo" << endl;
                                dano *= 3;
                            }else if(pontp2->getClasse() == "Mago"){
                                if(vidap2>=vidap1){
                                    dano = vidap1*0.1;
                                     cout << "fazendo com que seu dano seja 10% da vida do oponente" << endl;
                                }else{
                                    dano = vidap1*0.3;
                                    cout << "fazendo com que seu dano seja 30% da vida do oponente" << endl;
                                }                                
                            }else if(pontp2->getClasse() == "Mímico"){
                                cout << "copiando " << pontp1->getEspecial() << " e" << endl;
                                if(pontp1->getClasse() == "Arqueiro"){
                                    dano = (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                    duracao_sangramentop1 += 2 + rand()%5;
                                    cout << "deixando " << pontp1->getnome() << " com " << duracao_sangramentop1 << " turnos de sangramento" << endl;
                                }else if(pontp1->getClasse() == "Espadachim"){
                                    dano = (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                    dano += (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                    cout << "realizando dois ataques" << endl;
                                }else if(pontp1->getClasse() == "Curandeiro"){
                                    dano = 0;
                                    int cura;
                                    cura = pontp2->getVID() *0.5;
                                    if(vidap2 + cura > pontp2->getVID()){
                                        cura = pontp2->getVID() - vidap2;

                                    }
                                    vidap2 += cura;
                                    cout << "curando sua vida em "<< cura << " pontos" << endl;
                                }else if(pontp1->getClasse() == "Bombardeiro"){
                                    dano = (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
									pontp2->soma_dano_total_sofrido(dano);
                            		pontp2->set_maior_dano_sofrido(dano);
                                    vidap2-=dano;
                               	     cout << "causando uma explosão e também " << dano << " de dano a si mesmo" << endl;
                                    dano *= 3;
                                }else if(pontp1->getClasse() == "Mago"){
                                    if(vidap2>=vidap1){
                                        dano = vidap1*0.1;
                                        cout << "fazendo com que seu dano seja 10% da vida do oponente" << endl;
                                    }else{
                                        dano = vidap1*0.3;
                                        cout << "fazendo com que seu dano seja 30% da vida do oponente" << endl;
                                    }                                
                                }else if(pontp1->getClasse() == "Mímico"){
                                    dano = (pontp2->getATQ() + (pontp2->getATQ() * (50+rand()%51)/100))/pontp1->getDEF();
                                    cout << "nada aconteceu" << endl;
                                }
                            }
                            contadorp2++;
                        }
                        danop2 += dano;
                        vidap1 -= dano;
                        pontp2->set_maior_dano_causado(dano);
                        pontp1->set_maior_dano_sofrido(dano);
                        if(vidap1>0){
                            cout << pontp2->getnome() << " atacou deu " << dano << " de dano, e deixou " << pontp1->getnome() << " com " << vidap1 << " de vida";
                        }else{
                            cout << pontp2->getnome() << " atacou deu " << dano << " de dano, e derrotou " << pontp1->getnome() << endl << endl;
                        }
                        r++;
						this_thread::sleep_for(chrono::seconds(Configuracoes::get_tempo_espera())); 
                    }
                    t++;
                }                            
            }
            int random = rand()%2;
            if(vidap1<0){
                vidap1=0;
            }
            if(vidap2<0){
                vidap2=0;
            }
            pontp1->soma_dano_total_causado(danop1);
            pontp1->soma_dano_total_sofrido(danop2);
            pontp2->soma_dano_total_causado(danop2);
            pontp2->soma_dano_total_sofrido(danop1);
            if((r<=max_turno && ((vidap1>vidap2) || (vidap1==vidap2 && danop1>danop2) || (danop1==danop2 && (vidap1==vidap2 && random==0)))) || (r>max_turno && ((danop1>danop2) || (danop1==danop2 && (vidap1>vidap2) || (vidap1==vidap2 && random==0))))){
                if(r>10 && max_turno==10){
                    r=10;
                }else if(r>100 && max_turno==50){
                	r=50;
				}
                cout << "\n\n-------------------------ESTATÍSTICAS-------------------------";
                cout << "\n\nVencedor !!\t\t\tPerdedor !" << endl;
                cout << pontp1->getnome() << "\t\t\t\t" << pontp2->getnome() << endl;
                cout << "Vida Restante: " << vidap1 << "\t\t" << "Vida Restante: " << vidap2 << endl;
                cout << "Dano Causado: "  << danop1 << "\t\t" << "Dano Causado: "  << danop2 << endl;
                cout << "ATKs Especiais: "  << contadorp1 << "\t\t" << "ATKs Especiais: "  << contadorp2 << endl;
                cout << "\n\t\tRounds Ocorridos: " << r << endl;
                pontp1->add_derrotado(pontp2);
                cout << endl << endl << "Presione Qualquer Tecla para Prosseguir...";
				_getch();
				system("cls");
                p1_venceu=true;
            }else{
                if(r>10 && max_turno==10){
                    r=11;
                }else if(r>100 && max_turno==50){
                	r=51;
				}
                cout << "\n\n-------------------------ESTATÍSTICAS-------------------------";
                cout << "\n\nPerdedor !\t\t\tVencedor !!" << endl;
                cout << pontp1->getnome() << "\t\t\t\t" << pontp2->getnome() << endl;
                cout << "Vida Restante: " << vidap1 <<"\t\t" << "Vida Restante: " << vidap2 << endl;
                cout << "Dano Causado: "  << danop1 << "\t\t" << "Dano Causado: "  << danop2 << endl;
                cout << "ATKs Especiais: "  << contadorp1 << "\t\t" << "ATKs Especiais: "  << contadorp2 << endl;
                cout << "\n\t\tRounds Ocorridos: " << r-1 << endl;
                pontp2->add_derrotado(pontp1);
                cout << endl << endl << "Presione Qualquer Tecla para Prosseguir...";
				_getch();
				system("cls");
                p1_venceu=false;
            } 
			if(p1_jogador){
	        	if(p1_venceu){
	        		return vidap1;
				}else{
					return 0;
				}
			}else{
				if(!p1_venceu){
	        		return vidap2;
				}else{
					return 0;
				}
			}        
        }
        Personagem criar_personagem(){
        	
            char op;
            cout << "\nSelecione a classe desejada: \n\n";
            cout << "1- Arqueiro\n";
            cout << "2- Espadachim\n";
            cout << "3- Curandeiro \n";
            cout << "4- Bombardeiro \n";
            cout << "5- Mago \n";
            op = _getch() ;

            string nome;
       
            while(op<'1' || op>'5'){            
                op = _getch() ;
            }
            switch(op){
                case '1':
                    {
                    cout  << "Digite o nome do personagem: ";
                    getline(cin, nome);
                    Arqueiro p = Arqueiro(nome);
                    return p;
                    }
                break;

                case '2':
                    {
                    cout  << "Digite o nome do personagem: ";
                    getline(cin, nome);
                    Espadachim p = Espadachim(nome);
                    return p;
                    }
                break;

                case '3':
                    {
                    cout  << "Digite o nome do personagem: ";
                    getline(cin, nome);
                    Curandeiro p = Curandeiro(nome);
                    return p;
                    }
                break;

                case '4':
                    {
                    cout  << "Digite o nome do personagem: ";
                    getline(cin, nome);
                    Bombardeiro p = Bombardeiro(nome);
                    return p;
                    }
                break;
                
                case '5':
                    {
                    cout  << "Digite o nome do personagem: ";
                    getline(cin, nome);
                    Mago p = Mago(nome);
                    return p;
                    }
                break;

            }      
        }
    
};

class Sala{
	private:
		bool topo,esquerda,direita,baixo,tesouro,inimigo;;
	public:
		Sala(bool topo,bool esquerda,bool direita,bool baixo,bool tesouro){
			this->topo=topo;
			this->esquerda = esquerda;
			this->direita=direita;
			this->baixo=baixo;
			this->tesouro=tesouro;
			this->inimigo=0;
		}
		bool get_topo(){
			return topo;
		}
		void set_topo(bool topo){
			this->topo = topo;
		}
		bool get_esquerda(){
			return esquerda;
		}
		void set_esquerda(bool esquerda){
			this->esquerda = esquerda;
		}
		bool get_direita(){
			return direita;
		}
		void set_direita(bool direita){
			this->direita = direita;
		}
		bool get_baixo(){
			return baixo;
		}
		void set_baixo(bool tesouro){
			this->baixo = baixo;
		}
		bool get_tesouro(){
			return tesouro;
		}
		void set_tesouro(bool tesouro){
			this->tesouro = tesouro;
		}
		bool get_inimigo(){
			return inimigo;
		}
		void set_inimigo(bool inimigo){
			this->inimigo = inimigo;
		}
};

class Criatura{
	protected:
		int x,y;
		Console c;
		Personagem *personagem;
	public:
		Criatura(){}
		Criatura(Personagem *personagem){
			this->personagem = personagem;
			x=0;
			y=0;
		}
		int get_x(){
			return x;
		}
		void set_x(int x){
			this->x = x;
		}
		int get_y(){
			return y;
		}
		void set_y(int y){
			this->y = y;
		}
		Personagem *get_personagem(){
			return personagem;
		}
		void set_personagem(Personagem *personagem){
			this->personagem = personagem;
		}
		void apagar_personagem(){
			c.set_cursor((x*5)+3,(y*2)+1);
			cout << "\b ";
		}
		virtual void escrever_personagem(){
			c.set_cursor((x*5)+3,(y*2)+1);
			c.print_color("\b#",9);
			c.set_cursor(0,0);
			c.set_cursor((largura*5)+1,altura*2);
		}
};

class Jogador:public Criatura{
	private:
		float vida_atual,capacete,peitoral,calca,bota;
		int tesouros[3],pocoes[3],pontuacao;
	public:
		Jogador(){}
		Jogador(Personagem *p):Criatura(p){
			capacete=0;
			peitoral=0;
			calca=0;
			bota=0;
			vida_atual = p->getVID();
			for(int i=0;i<3;i++){
				tesouros[i]=0;
			}
			for(int i=0;i<3;i++){
				pocoes[i]=0;
			}
			pontuacao = 0;
		}
		float get_vida_atual(){
			return vida_atual;
		}
		void set_vida_atual(float vida_atual){
			this->vida_atual = vida_atual;
		}
		
		float get_capacete(){
			return capacete;
		}
		void set_capacete(float capacete){
			if(this->capacete!=0){
				personagem->setDEF(personagem->getDEF()-capacete);
			}
			this->capacete = capacete;
			personagem->setDEF(personagem->getDEF()+capacete);
		}
		float get_peitoral(){
			return peitoral;
		}
		void set_peitoral(float peitoral){
			if(this->peitoral!=0){
				personagem->setDEF(personagem->getDEF()-peitoral);
			}
			this->peitoral = peitoral;
			personagem->setDEF(personagem->getDEF()+peitoral);
		}
		
		float get_calca(){
			return calca;
		}
		void set_calca(float calca){
			if(this->calca!=0){
				personagem->setDEF(personagem->getDEF()-calca);
			}
			this->calca = calca;
			personagem->setDEF(personagem->getDEF()+calca);
		}
		
		float get_bota(){
			return bota;
		}
		void set_bota(float bota){
			if(this->bota!=0){
				personagem->setDEF(personagem->getDEF()-bota);
			}
			this->bota = bota;
			personagem->setDEF(personagem->getDEF()+bota);
		}
		int get_pontuacao(){
			return pontuacao;
		}
		void set_pontuacao(){
			for(int i=0;i<3;i++){
				this->pontuacao += tesouros[i];
			}
		}
		void set_pontuacao(int pontuacao){
			this->pontuacao += pontuacao;
		}
		int get_tesouros(){
			int total = 0;
			for(int i=0;i<3;i++){
				total += tesouros[i];
			}
			return total;
		}
		int get_tesouros(int i){
			return tesouros[i];
		}
		void set_tesouros(int tesouro,int i){
			this->tesouros[i] = tesouro;
		}
		int get_pocoes(int i){
			return pocoes[i];
		}
		void set_pocoes(int pocoes,int i){
			this->pocoes[i] = pocoes;
		}
		void usar_pocao(int i){
			if(pocoes[i]!=0){
				system("cls");
				if(vida_atual+pocoes[i]>personagem->getVID()){					
					cout << "Você usou uma poção e curou " <<  personagem->getVID() - vida_atual << " pontos de vida!";
					vida_atual = personagem->getVID();
				}else{
				 	vida_atual += pocoes[i];
				 	cout << "Você usou uma poção e curou " <<  pocoes[i] << " pontos de vida!";
				}
				pocoes[i] = 0;
				cout << endl << endl << "Presione Qualquer Tecla para Prosseguir...";
				_getch();
				system("cls");
			}
			
		}
		
};

class Inimigo:public Criatura{
	public:
		Inimigo(){
		}
		Inimigo(int x,int y,Personagem *p):Criatura(p){
			this->x = x;
			this->y = y;
		}
		void escrever_personagem() override{
			c.set_cursor((x*5)+3,(y*2)+1);
			c.print_color("\b#",4);
			c.set_cursor((largura*5)+1,altura*2);
		}
};

class BOSS:public Inimigo{
	public:
		BOSS(){
		}
		BOSS(int x,int y,Personagem *p):Inimigo(x,y,p){
			p->setVID(p->getVID()*1.1);
			p->setATQ(p->getATQ()*1.1);
			p->setDEF(p->getDEF()*1.1);
		}
		void escrever_personagem() override{
			c.set_cursor((x*5)+3,(y*2)+1);
			c.print_color("\b#",5);
			c.set_cursor((largura*5)+1,altura*2);
		}
};

class Labirinto{
	private:
		Sala *labirinto[altura][largura];
		Jogador *jogador;
		bool venceu;
		Console c;
		list<Inimigo*> inimigos;
		BOSS *boss;
		
	public:
		Labirinto(Jogador *jogador,BOSS *boss){
			venceu = false;
			this->jogador = jogador;
			jogador->set_capacete(0.5);
			jogador->set_peitoral(0.5);
			jogador->set_calca(0.5);
			jogador->set_bota(0.5);
			this->boss = boss;			
			labirinto[0][0] = new Sala(1,1,0,1,0);
		    labirinto[0][1] = new Sala(1,0,0,1,0);
		    labirinto[0][2] = new Sala(1,0,1,0,0);
		    labirinto[0][3] = new Sala(1,1,0,0,0);
		    labirinto[0][4] = new Sala(1,0,1,0,0);
		    labirinto[0][5] = new Sala(1,1,0,0,0);
		    labirinto[0][6] = new Sala(1,0,0,1,0);
		    labirinto[0][7] = new Sala(1,0,0,1,0);
		    labirinto[0][8] = new Sala(1,0,1,0,0);
		    labirinto[0][9] = new Sala(1,1,0,0,0);
		    labirinto[0][10] = new Sala(1,0,0,1,0);
		    labirinto[0][11] = new Sala(1,0,0,0,0);
		    labirinto[0][12] = new Sala(1,0,1,0,0);
		    labirinto[0][13] = new Sala(1,1,0,1,1);
		    labirinto[0][14] = new Sala(1,0,1,0,0);
		
		    labirinto[1][0] = new Sala(1,1,0,1,0);
		    labirinto[1][1] = new Sala(1,0,1,0,0);
		    labirinto[1][2] = new Sala(0,1,0,0,0);
		    labirinto[1][3] = new Sala(0,0,1,1,0);
		    labirinto[1][4] = new Sala(0,1,1,0,0);
		    labirinto[1][5] = new Sala(0,1,0,1,0);
		    labirinto[1][6] = new Sala(1,0,0,1,0);
		    labirinto[1][7] = new Sala(1,0,1,0,0);
		    labirinto[1][8] = new Sala(0,1,1,1,1);
		    labirinto[1][9] = new Sala(0,1,0,1,0);
		    labirinto[1][10] = new Sala(1,0,1,1,0);
		    labirinto[1][11] = new Sala(0,1,1,0,0);
		    labirinto[1][12] = new Sala(0,1,0,1,0);
		    labirinto[1][13] = new Sala(1,0,0,0,0);
		    labirinto[1][14] = new Sala(0,0,1,0,0);
		
		    labirinto[2][0] = new Sala(1,1,0,0,0);
		    labirinto[2][1] = new Sala(0,0,0,1,0);
		    labirinto[2][2] = new Sala(0,0,1,0,0);
		    labirinto[2][3] = new Sala(1,1,0,1,0);
		    labirinto[2][4] = new Sala(0,0,0,1,0);
		    labirinto[2][5] = new Sala(1,0,1,0,0);
		    labirinto[2][6] = new Sala(1,1,1,0,0);
		    labirinto[2][7] = new Sala(0,1,0,1,0);
		    labirinto[2][8] = new Sala(1,0,0,0,0);
		    labirinto[2][9] = new Sala(1,0,0,1,0);
		    labirinto[2][10] = new Sala(1,0,0,0,0);
		    labirinto[2][11] = new Sala(0,0,0,0,0);
		    labirinto[2][12] = new Sala(1,0,1,0,0);
		    labirinto[2][13] = new Sala(0,1,1,0,0);
		    labirinto[2][14] = new Sala(0,1,1,1,0);
		
		    labirinto[3][0] = new Sala(0,1,1,0,0);
		    labirinto[3][1] = new Sala(1,1,1,0,0);
		    labirinto[3][2] = new Sala(0,1,0,1,0);
		    labirinto[3][3] = new Sala(1,0,0,1,0);
		    labirinto[3][4] = new Sala(1,0,1,0,0);
		    labirinto[3][5] = new Sala(0,1,1,0,0);
		    labirinto[3][6] = new Sala(0,1,0,0,0);
		    labirinto[3][7] = new Sala(1,0,1,1,0);
		    labirinto[3][8] = new Sala(0,1,0,1,0);
		    labirinto[3][9] = new Sala(1,0,1,1,0);
		    labirinto[3][10] = new Sala(0,1,1,0,0);
		    labirinto[3][11] = new Sala(0,1,0,1,0);
		    labirinto[3][12] = new Sala(0,0,1,0,0);
		    labirinto[3][13] = new Sala(0,1,0,1,0);
		    labirinto[3][14] = new Sala(1,0,1,0,0);
		
		    labirinto[4][0] = new Sala(0,1,0,1,0);
		    labirinto[4][1] = new Sala(0,0,0,1,0);
		    labirinto[4][2] = new Sala(1,0,0,1,0);
		    labirinto[4][3] = new Sala(1,0,1,1,1);
		    labirinto[4][4] = new Sala(0,1,1,0,0);
		    labirinto[4][5] = new Sala(0,1,1,1,0);
		    labirinto[4][6] = new Sala(0,1,0,1,0);
		    labirinto[4][7] = new Sala(1,0,0,0,0);
		    labirinto[4][8] = new Sala(1,0,0,0,0);
		    labirinto[4][9] = new Sala(1,0,1,0,0);
		    labirinto[4][10] = new Sala(0,1,0,0,0);
		    labirinto[4][11] = new Sala(1,0,1,1,0);
		    labirinto[4][12] = new Sala(0,1,1,0,0);
		    labirinto[4][13] = new Sala(1,1,1,0,0);
		    labirinto[4][14] = new Sala(0,1,1,0,0);
		
		    labirinto[5][0] = new Sala(1,1,0,1,0);
		    labirinto[5][1] = new Sala(1,0,0,0,0);
		    labirinto[5][2] = new Sala(1,0,0,1,0);
		    labirinto[5][3] = new Sala(1,0,0,1,0);
		    labirinto[5][4] = new Sala(0,0,0,0,0);
		    labirinto[5][5] = new Sala(1,0,1,1,0);
		    labirinto[5][6] = new Sala(1,1,1,0,1);
		    labirinto[5][7] = new Sala(0,1,1,0,0);
		    labirinto[5][8] = new Sala(0,1,1,1,0);
		    labirinto[5][9] = new Sala(0,1,1,0,0);
		    labirinto[5][10] = new Sala(0,1,1,0,0);
		    labirinto[5][11] = new Sala(1,1,0,0,0);
		    labirinto[5][12] = new Sala(0,0,1,0,0);
		    labirinto[5][13] = new Sala(0,1,0,1,0);
		    labirinto[5][14] = new Sala(0,0,1,1,0);
		
		    labirinto[6][0] = new Sala(1,1,0,0,0);
		    labirinto[6][1] = new Sala(0,0,0,1,0);
		    labirinto[6][2] = new Sala(1,0,1,0,0);
		    labirinto[6][3] = new Sala(1,1,1,0,0);
		    labirinto[6][4] = new Sala(0,1,0,1,0);
		    labirinto[6][5] = new Sala(1,0,0,0,0);
		    labirinto[6][6] = new Sala(0,0,1,1,0);
		    labirinto[6][7] = new Sala(0,1,1,0,0);
		    labirinto[6][8] = new Sala(1,1,0,1,0);
		    labirinto[6][9] = new Sala(0,0,1,0,0);
		    labirinto[6][10] = new Sala(0,1,1,0,0);
		    labirinto[6][11] = new Sala(0,1,1,0,0);
		    labirinto[6][12] = new Sala(0,1,1,0,0);
		    labirinto[6][13] = new Sala(1,1,0,0,0);
		    labirinto[6][14] = new Sala(1,0,1,1,0);
		
		    labirinto[7][0] = new Sala(0,1,1,1,0);
		    labirinto[7][1] = new Sala(1,1,0,1,1);
		    labirinto[7][2] = new Sala(0,0,0,0,0);
		    labirinto[7][3] = new Sala(0,0,0,0,0);
		    labirinto[7][4] = new Sala(1,0,1,1,0);
		    labirinto[7][5] = new Sala(0,1,1,0,0);
		    labirinto[7][6] = new Sala(1,1,0,1,0);
		    labirinto[7][7] = new Sala(0,0,1,0,0);
		    labirinto[7][8] = new Sala(1,1,1,0,0);
		    labirinto[7][9] = new Sala(0,1,0,1,0);
		    labirinto[7][10] = new Sala(0,0,1,1,0);
		    labirinto[7][11] = new Sala(0,1,1,1,0);
		    labirinto[7][12] = new Sala(0,1,0,0,0);
		    labirinto[7][13] = new Sala(0,0,0,1,0);
		    labirinto[7][14] = new Sala(1,0,1,0,0);
		
		    labirinto[8][0] = new Sala(1,1,0,1,0);
		    labirinto[8][1] = new Sala(1,0,0,1,0);
		    labirinto[8][2] = new Sala(0,0,0,1,0);
		    labirinto[8][3] = new Sala(0,0,1,1,0);
		    labirinto[8][4] = new Sala(1,1,0,0,0);
		    labirinto[8][5] = new Sala(0,0,0,1,0);
		    labirinto[8][6] = new Sala(1,0,1,1,0);
		    labirinto[8][7] = new Sala(0,1,1,0,0);
		    labirinto[8][8] = new Sala(0,1,0,0,0);
		    labirinto[8][9] = new Sala(1,0,0,1,0);
		    labirinto[8][10] = new Sala(1,0,1,0,0);
		    labirinto[8][11] = new Sala(1,1,1,0,1);
		    labirinto[8][12] = new Sala(0,1,1,0,0);
		    labirinto[8][13] = new Sala(1,1,0,0,0);
		    labirinto[8][14] = new Sala(0,0,1,1,0);
		
		    labirinto[9][0] = new Sala(1,1,0,0,0);
		    labirinto[9][1] = new Sala(1,0,0,0,0);
		    labirinto[9][2] = new Sala(1,0,0,1,0);
		    labirinto[9][3] = new Sala(1,0,0,1,0);
		    labirinto[9][4] = new Sala(0,0,0,1,0);
		    labirinto[9][5] = new Sala(1,0,0,1,0);
		    labirinto[9][6] = new Sala(1,0,0,1,0);
		    labirinto[9][7] = new Sala(0,0,1,0,0);
		    labirinto[9][8] = new Sala(0,1,0,1,0);
		    labirinto[9][9] = new Sala(1,0,1,0,0);
		    labirinto[9][10] = new Sala(0,1,0,1,0);
		    labirinto[9][11] = new Sala(0,0,1,1,0);
		    labirinto[9][12] = new Sala(0,1,1,0,0);
		    labirinto[9][13] = new Sala(0,1,0,1,0);
		    labirinto[9][14] = new Sala(1,0,1,1,1);
		
		    labirinto[10][0] = new Sala(0,1,1,1,0);
		    labirinto[10][1] = new Sala(0,1,1,0,0);
		    labirinto[10][2] = new Sala(1,1,0,1,1);
		    labirinto[10][3] = new Sala(1,0,0,0,0);
		    labirinto[10][4] = new Sala(1,0,1,1,0);
		    labirinto[10][5] = new Sala(1,1,1,0,0);
		    labirinto[10][6] = new Sala(1,1,1,0,0);
		    labirinto[10][7] = new Sala(0,1,1,0,0);
		    labirinto[10][8] = new Sala(1,1,1,0,1);
		    labirinto[10][9] = new Sala(0,1,0,0,0);
		    labirinto[10][10] = new Sala(1,0,0,1,0);
		    labirinto[10][11] = new Sala(1,0,0,0,0);
		    labirinto[10][12] = new Sala(0,0,1,1,0);
		    labirinto[10][13] = new Sala(1,1,0,0,0);
		    labirinto[10][14] = new Sala(1,0,1,0,0);
		
		    labirinto[11][0] = new Sala(1,1,0,1,0);
		    labirinto[11][1] = new Sala(0,0,0,1,0);
		    labirinto[11][2] = new Sala(1,0,1,0,0);
		    labirinto[11][3] = new Sala(0,1,0,1,0);
		    labirinto[11][4] = new Sala(1,0,0,0,0);
		    labirinto[11][5] = new Sala(0,0,0,0,0);
		    labirinto[11][6] = new Sala(0,0,1,1,0);
		    labirinto[11][7] = new Sala(0,1,0,1,0);
		    labirinto[11][8] = new Sala(0,0,1,1,0);
		    labirinto[11][9] = new Sala(0,1,1,0,0);
		    labirinto[11][10] = new Sala(1,1,1,0,0);
		    labirinto[11][11] = new Sala(0,1,1,0,0);
		    labirinto[11][12] = new Sala(1,1,0,0,0);
		    labirinto[11][13] = new Sala(0,0,1,1,0);
		    labirinto[11][14] = new Sala(0,1,1,0,0);
		
		    labirinto[12][0] = new Sala(1,1,0,0,0);
		    labirinto[12][1] = new Sala(1,0,1,1,1);
		    labirinto[12][2] = new Sala(0,1,0,0,0);
		    labirinto[12][3] = new Sala(1,0,0,1,0);
		    labirinto[12][4] = new Sala(0,0,1,1,0);
		    labirinto[12][5] = new Sala(0,1,1,1,0);
		    labirinto[12][6] = new Sala(1,1,0,0,0);
		    labirinto[12][7] = new Sala(1,0,0,1,0);
		    labirinto[12][8] = new Sala(1,0,0,1,0);
		    labirinto[12][9] = new Sala(0,0,1,1,0);
		    labirinto[12][10] = new Sala(0,1,0,1,0);
		    labirinto[12][11] = new Sala(0,0,1,1,0);
		    labirinto[12][12] = new Sala(0,1,1,0,0);
		    labirinto[12][13] = new Sala(1,1,0,0,0);
		    labirinto[12][14] = new Sala(0,0,1,0,0);
		
		    labirinto[13][0] = new Sala(0,1,0,1,0);
		    labirinto[13][1] = new Sala(1,0,0,1,0);
		    labirinto[13][2] = new Sala(0,0,0,1,0);
		    labirinto[13][3] = new Sala(1,0,1,1,0);
		    labirinto[13][4] = new Sala(1,1,0,0,0);
		    labirinto[13][5] = new Sala(1,0,0,1,0);
		    labirinto[13][6] = new Sala(0,0,0,1,0);
		    labirinto[13][7] = new Sala(1,0,0,1,0);
		    labirinto[13][8] = new Sala(1,0,0,1,0);
		    labirinto[13][9] = new Sala(1,0,0,1,0);
		    labirinto[13][10] = new Sala(1,0,0,1,0);
		    labirinto[13][11] = new Sala(1,0,0,1,0);
		    labirinto[13][12] = new Sala(0,0,1,0,0);
		    labirinto[13][13] = new Sala(0,1,0,1,1);
		    labirinto[13][14] = new Sala(0,0,1,1,0);
		
		    labirinto[14][0] = new Sala(1,1,0,1,1);
		    labirinto[14][1] = new Sala(1,0,0,1,0);
		    labirinto[14][2] = new Sala(1,0,0,1,0);
		    labirinto[14][3] = new Sala(1,0,0,1,0);
		    labirinto[14][4] = new Sala(0,0,0,1,0);
		    labirinto[14][5] = new Sala(1,0,0,1,0);
		    labirinto[14][6] = new Sala(1,0,0,1,0);
		    labirinto[14][7] = new Sala(1,0,0,1,0);
		    labirinto[14][8] = new Sala(1,0,1,1,0);
		    labirinto[14][9] = new Sala(1,1,0,1,0);
		    labirinto[14][10] = new Sala(1,0,0,1,0);
		    labirinto[14][11] = new Sala(1,0,0,1,0);
		    labirinto[14][12] = new Sala(0,0,0,1,0);
		    labirinto[14][13] = new Sala(1,0,0,1,0);
		    labirinto[14][14] = new Sala(1,0,1,1,0);
			labirinto[boss->get_y()][boss->get_x()]->set_inimigo(1);
		}
		
		~Labirinto(){
			for (int i = 0; i < altura; i++) {
				for (int j = 0; j <largura; j++) {
					delete labirinto[i][j];
				}
			}
			
		}
		
		bool andar_esquerda(){	
			if(!labirinto[jogador->get_y()][jogador->get_x()]->get_esquerda()){
				jogador->apagar_personagem();
				jogador->set_x(jogador->get_x()-1);
				jogador->escrever_personagem();
				return true;
			}
			return false;
		}
		bool andar_cima(){
			if(!labirinto[jogador->get_y()][jogador->get_x()]->get_topo()){
				jogador->apagar_personagem();
				jogador->set_y(jogador->get_y()-1);
				jogador->escrever_personagem();
				return true;
			}
			return false;
		}
		bool andar_baixo(){
			if(!labirinto[jogador->get_y()][jogador->get_x()]->get_baixo()){
				jogador->apagar_personagem();
				jogador->set_y(jogador->get_y()+1);
				jogador->escrever_personagem();
				return true;
			}
			return false;
		}
		bool andar_direita(){		
			if(!labirinto[jogador->get_y()][jogador->get_x()]->get_direita()){
				jogador->apagar_personagem();
				jogador->set_x(jogador->get_x()+1);
				jogador->escrever_personagem();
				return true;
			}
			return false;
		}
		bool andar_esquerda(Inimigo *inimigo){	
			if(!labirinto[inimigo->get_y()][inimigo->get_x()]->get_esquerda()){
				if(!labirinto[inimigo->get_y()][inimigo->get_x()-1]->get_inimigo()){
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(0);
					inimigo->apagar_personagem();
					inimigo->set_x(inimigo->get_x()-1);
					inimigo->escrever_personagem();
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(1);
				}
				return true;
			}
			return false;			
		}
		bool andar_cima(Inimigo *inimigo){
			if(!labirinto[inimigo->get_y()][inimigo->get_x()]->get_topo()){
				if(!labirinto[inimigo->get_y()-1][inimigo->get_x()]->get_inimigo()){
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(0);
					inimigo->apagar_personagem();
					inimigo->set_y(inimigo->get_y()-1);
					inimigo->escrever_personagem();
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(1);
				}
				return true;
			}
			return false;
		}
		bool andar_baixo(Inimigo *inimigo){
			if(!labirinto[inimigo->get_y()][inimigo->get_x()]->get_baixo()){
				if(!labirinto[inimigo->get_y()+1][inimigo->get_x()]->get_inimigo()){
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(0);
					inimigo->apagar_personagem();
					inimigo->set_y(inimigo->get_y()+1);
					inimigo->escrever_personagem();
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(1);
				}
				return true;
			}
			return false;
		}
		bool andar_direita(Inimigo *inimigo){		
			if(!labirinto[inimigo->get_y()][inimigo->get_x()]->get_direita()){
				if(!labirinto[inimigo->get_y()][inimigo->get_x()+1]->get_inimigo()){
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(0);
					inimigo->apagar_personagem();
					inimigo->set_x(inimigo->get_x()+1);
					inimigo->escrever_personagem();
					labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(1);
				}
				return true;
			}
			return false;
		}
		
		void abrir_bau(){
			
			if(labirinto[jogador->get_y()][jogador->get_x()]->get_tesouro()){
				sortear_armadura();
				sortear_pocao();
				sortear_tesouro();
				labirinto[jogador->get_y()][jogador->get_x()]->set_tesouro(0);
				system("cls");
				mostrar_labirinto();
			}
		}
		
		void sortear_armadura(){
			int armadura = rand()%4;
			int qualidade = rand()%4;
			char o;
			float defesa;
			string str_armadura;
			string str_qualidade;
			switch(qualidade){
				case 0:
					defesa = -0.5;
					str_qualidade = "Amaldiçoado(a)";
					break;
				case 1:
					defesa = 1;
					str_qualidade = "Velho(a)";
					break;
				case 2:
					defesa = 1.5;
					str_qualidade = "Resistente";
					break;
				case 3:
					defesa = 2;
					str_qualidade = "Sagrado(a)";
					break;
			}
			switch(armadura){
				case 0:
					str_armadura = "Capacete";
					break;
				case 1:
					str_armadura = "Peitoral";
					break;
				case 2:
					str_armadura = "Calça";
					break;
				case 3:
					str_armadura = "Bota";
					break;
			}
			system("cls");
			cout << endl << "Capacete:" << jogador->get_capacete();
			cout << endl << "Peitoral:" << jogador->get_peitoral();
			cout << endl << "Calca:" << jogador->get_calca();
			cout << endl << "Bota:" << jogador->get_bota();
			cout << "\nVocê recebeu um(a) " << str_armadura << " " << str_qualidade << "(" << defesa << " DEF)";
		
			if(defesa>0){
				cout << "\nDeseja equipar?\n1-SIM \t2-NÃO";
				o = _getch();
				while(o!='1' && o!='2'){
					o = _getch();
				}
			}else{
				o = '1';
				cout << endl << "A armadura se equipa em você por vontade prórpia";
				cout << endl << endl << "Presione Qualquer Tecla para Prosseguir...";
				_getch();
			}
			if(o == '1'){
				switch(armadura){
					case 0:
						jogador->set_capacete(defesa);
						break;
					case 1:
						jogador->set_peitoral(defesa);
						break;
					case 2:
						jogador->set_calca(defesa);
						break;
					case 3:
						jogador->set_bota(defesa);
						break;
				}
			}
		}
		void sortear_tesouro(){
			int preciosidade = rand()%6,pontos;
			string nome;
			char o;
			switch(preciosidade){
				case 0:
					pontos = 100;
					nome = "Colar Enferrujado";
					break;
				case 1:
					pontos = 250;
					nome = "Bracelete de Pérolas";
					break;
				case 2:
					pontos = 500;
					nome = "Pepita de Ouro";
					break;
				case 3:
					pontos = 750;
					nome = "Bracelete de Esmeraldas";
					break;
				case 4:
					pontos = 1000;
					nome = "Colar de Rubi";
					break;
				case 5:
					pontos = 1500;
					nome = "Anel de Diamante";
					break;
			}
			system("cls");
			cout << endl << "Bolso de Tesouros:" << endl;
			for(int i =0;i<3;i++){
				cout << endl << "["<< i << "]: +" << jogador->get_tesouros(i) << " pts";
			}
			
			cout << "\nVocê recebeu um(a) " << nome << " (+" << pontos << " pts)";
			cout << "\nEm qual slot deseja guardar?\n0-[0] \t1-[1] \t2-[2] \t3-Nenhum";
			o = _getch();
			while(o!='0' && o!='1' && o!='2' && o!='3'){
				o = _getch();
			}

			switch(o){
				case '0':
					jogador->set_tesouros(pontos,0);
					break;
				case '1':
					jogador->set_tesouros(pontos,1);
					break;
				case '2':
					jogador->set_tesouros(pontos,2);
					break;
			}
			
		}
		
		void sortear_pocao(){
			int cura = rand()%3,pontos_vida;
			string nome;
			char o;
			switch(cura){
				case 0:
					pontos_vida = 250;
					nome = "Remédio Caseiro";
					break;
				case 1:
					pontos_vida = 500;
					nome = "Poção Básica";
					break;
				case 2:
					pontos_vida = 1000;
					nome = "Poção Suprema";
					break;
			}
			system("cls");
			cout << endl << "Bolso de Poções:" << endl;
			for(int i =0;i<3;i++){
				cout << endl << "["<< i << "]: +" << jogador->get_pocoes(i) << " pts de vida";
			}
			
			cout << "\nVocê recebeu um(a) " << nome << " (+" << pontos_vida << " pts)";
			cout << "\nEm qual slot deseja guardar?\n0-[0] \t1-[1] \t2-[2] \t3-Nenhum";
			o = _getch();
			while(o!='0' && o!='1' && o!='2' && o!='3'){
				o = _getch();
			}

			switch(o){
				case '0':
					jogador->set_pocoes(pontos_vida,0);
					break;
				case '1':
					jogador->set_pocoes(pontos_vida,1);
					break;
				case '2':
					jogador->set_pocoes(pontos_vida,2);
					break;
			}
			
		}
		
		
		bool batalha(Inimigo *inimigo,bool p1_jogador,int max_turno){
			JogoRPG j;
			float vida_jogador;
			if(p1_jogador){
				vida_jogador = j.batalha(jogador->get_personagem(),inimigo->get_personagem(),p1_jogador,jogador->get_vida_atual(),max_turno);
			}else{
				vida_jogador = j.batalha(inimigo->get_personagem(),jogador->get_personagem(),p1_jogador,jogador->get_vida_atual(),max_turno);
			}
			if(vida_jogador>0){				
				remove_inimigo(inimigo);
				jogador->set_vida_atual(vida_jogador);
				if(max_turno==10){
					cout << "Você ganhou 1000 pontos por derrotar esse inimigo";
					jogador->set_pontuacao(1000);
					cout << endl << endl << "Presione Qualquer Tecla para Prosseguir...";
					_getch();
					system("cls");
				}else{
					cout << "Você ganhou 10000 pontos por derrotar o grande Boss";
					jogador->set_pontuacao(10000);
					cout << endl << endl << "Presione Qualquer Tecla para Prosseguir...";
					_getch();
					venceu = true;
					system("cls");
				}
			}
			mostrar_labirinto();
			if(vida_jogador>0){
				return true;
			}else{
				return false;
			}
		}
		
		void mostrar_labirinto(){
			setlocale(LC_ALL,"C");
			system("cls");
			for(int i=0;i<altura;i++){
				for(int j=0;j<largura;j++){
					if(i==0){
						for(int k = 0;k<5;k++){
							cout << char(219);
						}
					}
				}
				if(i==0){
					cout << endl;
				}
				for(int j=0;j<largura;j++){
					if(labirinto[i][j]->get_esquerda() && labirinto[i][j]->get_tesouro()){
						cout << char(219);
						c.print_color("O  ",6);
					}else if(labirinto[i][j]->get_esquerda() && !labirinto[i][j]->get_tesouro()){
						cout << char(219);
						cout << "   ";
						
					}else if(!labirinto[i][j]->get_esquerda() && labirinto[i][j]->get_tesouro()){
						cout<< "   ";
						c.print_color("O",6);
					}else{
						cout << "    ";
					}
					if(labirinto[i][j]->get_direita()){
						cout << char(219);
					}else{
						cout << " ";
					}
				}
				cout << endl;
				for(int j=0;j<largura;j++){
					if(labirinto[i][j]->get_baixo()){
						for(int k = 0;k<5;k++){
							cout << char(219);
						}
					}else if(j==0){
						cout << char(219);
						cout << "   ";
						if(i!=altura-1){
							if(labirinto[i+1][j]->get_direita()||labirinto[i][j]->get_direita()){
								cout << char(219);
							}else{
								cout << " ";	
							}
						}
					}else if(j==largura-1){
						if(i!=altura-1){
							if(labirinto[i+1][j]->get_esquerda()||labirinto[i][j]->get_esquerda()){
								cout << char(219);
							}else{
								cout << " ";	
							}
						}
						cout << "   ";
						cout << char(219);
					}else{
						if(i!=altura-1){
							if(labirinto[i+1][j]->get_esquerda()||labirinto[i][j]->get_esquerda()){
								cout << char(219);
							}else{
								cout << " ";	
							}
						}
						cout << "   ";
						if(i!=altura-1){
							if(labirinto[i+1][j]->get_direita()||labirinto[i][j]->get_direita()){
								cout << char(219);
							}else{
								cout << " ";	
							}
						}
					}
				}
				cout << endl;
			}
			setlocale(LC_ALL,"");
			cout << endl;
			cout << endl << "Controles:";
			cout << endl << "W - Andar Para Cima";
			cout << "\t" << "A - Andar Para a Esquerda";
			cout << "\t" << "D - Andar Para a Direita";
			cout << "\t" << "S - Andar Para Baixo";
			cout << "\t" << "O - Abrir Baú";
			cout << "\t" << "0/1/2 - Usar Poção";
			cout << endl << endl << "Status:";
			cout << endl << "Vida: " << jogador->get_vida_atual() << "/" << jogador->get_personagem()->getVID();
			cout << "\t" << "ATQ: " << jogador->get_personagem()->getATQ();
			cout << "\t" << "DEF: " << jogador->get_personagem()->getDEF();
			cout << "\t" << "Capacete: " << jogador->get_capacete();
			cout << "\t" << "Peitoral: " << jogador->get_peitoral();
			cout << "\t" << "Calca: " << jogador->get_calca();
			cout << "\t" << "Bota: " << jogador->get_bota();
			cout << "\t" << "Pontos: " << jogador->get_pontuacao()+jogador->get_tesouros();
			cout << endl << endl << "Bolso de poções:" << endl;
			for(int i=0;i<3;i++){
				cout << "["<<i<<"]: +" << jogador->get_pocoes(i)<<" pts de vida\t";
			}
			cout << endl << endl << "Bolso de tesouros:" << endl;
			for(int i=0;i<3;i++){
				cout << "["<<i<<"]: +" << jogador->get_tesouros(i)<<" pts\t";
			}
			jogador->escrever_personagem();
			for(Inimigo* &i :  inimigos){
				i->escrever_personagem();
            }
            boss->escrever_personagem();
		}
		void add_inimigo(Inimigo *inimigo){
            inimigos.push_back(inimigo);
            labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(1);
        }
        void remove_inimigo(Inimigo *inimigo){
        	labirinto[inimigo->get_y()][inimigo->get_x()]->set_inimigo(0);
        	inimigos.remove(inimigo);
		}
		bool andar_inimigo(){
			bool retorno;
			for(Inimigo* &i :  inimigos){
				int aleatorio;
                do{
                	aleatorio = rand()%5;
                	if(aleatorio==0){
                		retorno = andar_cima(i);
					}else if(aleatorio==1){
                		retorno = andar_esquerda(i);
					}else if(aleatorio==2){
                		retorno = andar_direita(i);
					}else{
                		retorno = andar_baixo(i);
					}
				}while(!retorno);
				if(i->get_x() == jogador->get_x() && i->get_y() == jogador->get_y()){
					cout << endl << endl << "Um Inimigo Entrou em Batalha com Você. Presione Qualquer Tecla para Prosseguir...";
					_getch();	
					return batalha(i,0,10);
				}	
            }
            return true;
		}
		bool verifica_inimigo(){
			if(labirinto[jogador->get_y()][jogador->get_x()]->get_inimigo()){
				cout << endl << endl << "Você Entrou em Batalha com Um Inimigo. Presione Qualquer Tecla para Prosseguir...";
				_getch();
				for(Inimigo* &i :  inimigos){
					if((i->get_x() == jogador->get_x()) && (i->get_y() == jogador->get_y())){
						return batalha(i,1,10);
					}
				}
				batalha(boss,1,50);
				return false;
			}
			return true;
		}
		Jogador* get_jogador(){
			return jogador;
		}
		bool get_venceu(){
			return venceu;
		}
		void set_venceu(bool venceu){
			this->venceu = venceu;
		}

};

int main() {
	char repetir;
	do{	
		system("cls");
		setlocale(LC_ALL,"");
		Console c;
		JogoRPG jr;
		srand(time(0));
		c.tela_cheia();
		Personagem personagem_jogador = jr.criar_personagem();
		char o_velocidade;
		do{
			
			system("cls");
			cout << "Selecione uma Velocidade de Batalha\n1- Rápido\n2- Médio\n3- Lento\n";
			o_velocidade = _getch();
			switch(o_velocidade){
			case '1':
				Configuracoes(0);
				break;
			case '2':
				Configuracoes(1);
				break;
			case '3':
				Configuracoes(4);
				break;
			default:
				system("cls");
				cout<<"Por Favor Digite uma Opção Válida!!!\n";
			}
		}while(o_velocidade != '1' && o_velocidade != '2'  && o_velocidade != '3' );
		system("cls");
		Jogador j = Jogador(&personagem_jogador);
		Mimico m = Mimico("Mr. Mime(BOSS)");
		BOSS boss = BOSS(14,14,&m);
		Labirinto l = Labirinto(&j,&boss);
		Curandeiro c1 = Curandeiro("Alma Vermelha");
		Arqueiro c2 = Arqueiro("Robin Hood");
		Espadachim c3 = Espadachim("Sharpness");
		Mago c4 = Mago("Magnus o Mago");
		Bombardeiro c5 = Bombardeiro("Nuclear");
		Mago c6 = Mago("Arcano Místico");
		Arqueiro c7 = Arqueiro("Ponta Dourada");
		Bombardeiro c8 = Bombardeiro("Radioativo");
		Espadachim c9 = Espadachim("Roronoa Zoro");
		Bombardeiro c10 = Bombardeiro("Atômico");
		Curandeiro c11 = Curandeiro("Lux");
		Inimigo i1 = Inimigo(1,6,&c1);
		Inimigo i2 = Inimigo(2,5,&c2);
		Inimigo i3 = Inimigo(3,13,&c3);
		Inimigo i4 = Inimigo(7,5,&c4);
		Inimigo i5 = Inimigo(5,8,&c5);
		Inimigo i6 = Inimigo(6,13,&c6);
		Inimigo i7 = Inimigo(4,2,&c7);
		Inimigo i8 = Inimigo(8,3,&c8);
		Inimigo i9 = Inimigo(11,3,&c9);
		Inimigo i10 = Inimigo(11,10,&c10);
		Inimigo i11 = Inimigo(14,3,&c11);	
		l.add_inimigo(&i1);	
		l.add_inimigo(&i2);
		l.add_inimigo(&i3);
		l.add_inimigo(&i4);
		l.add_inimigo(&i5);
		l.add_inimigo(&i6);
		l.add_inimigo(&i7);
		l.add_inimigo(&i8);
		l.add_inimigo(&i9);
		l.add_inimigo(&i10);
		l.add_inimigo(&i11);
		l.mostrar_labirinto();
		char tecla;
		bool jogo_continua=true;
		while(jogo_continua){
			tecla = _getch();
			bool moveu = false;
			switch(tecla){
				case 'w':
				case 'W':	
					moveu = l.andar_cima();
					break;
				case 'a':
				case 'A':
					moveu = l.andar_esquerda();
					break;
				case 'd':
				case 'D':
					moveu = l.andar_direita();;	
					break;
				case 's':
				case 'S':
					moveu = l.andar_baixo();
					break;
				case 'o':
				case 'O':
					l.abrir_bau();
					break;
				case 'f':
				case 'F':
					return 0;
					break;
				case '0':
					l.get_jogador()->usar_pocao(0);
					l.mostrar_labirinto();
					break;
				case '1':
					l.get_jogador()->usar_pocao(1);
					l.mostrar_labirinto();
					break;
				case '2':
					l.get_jogador()->usar_pocao(2);
					l.mostrar_labirinto();
					break;
			}
			if(moveu){
				jogo_continua = l.verifica_inimigo();
				if(jogo_continua){
					jogo_continua = l.andar_inimigo();
				}
			}
		}
		system("cls");
		l.get_jogador()->set_pontuacao();
		if(!l.get_venceu()){
			c.print_color("GAME OVER",4);
			cout << endl << "Sua Pontuacao: " <<  l.get_jogador()->get_pontuacao();
		}else{
			c.print_color("VOCÊ VENCEU O LABIRINTO!PARABÉNS!!!",2);
			cout << endl << "Sua Pontuacao: " <<  l.get_jogador()->get_pontuacao();
		}
		l.get_jogador()->get_personagem()->mostrar();
		cout << "\n\nSe Deseja jogar novamente digite 1 se não digite qualquer outro caractere.\n";
		repetir = _getch();
	}while(repetir=='1');
	return 0;
}
