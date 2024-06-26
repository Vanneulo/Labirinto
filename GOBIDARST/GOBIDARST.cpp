#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //Para o uso do getch()
#include<ctype.h> //Para transformar o comando do usuario em maiusculo
#include<time.h> //Para pegar numeros aleatorios
#include <windows.h>//Inclui Beep.


//Struct definido as caracteristicas das salas. Typedef serve para definir a struct como uma variavel, assim evita colocar struct toda a hora.
typedef struct Sala
{
    char *descricao;
    struct Sala *norte;
    struct Sala *sul;
    struct Sala *leste;
    struct Sala *oeste;
    int chave;
} Sala; //Sala vai ser o nome da variavel struct Sala

//Funcao para criar uma sala dentro da main.
Sala* criarSala(char *descricao, int chave)
{
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    novaSala->descricao = descricao;
    novaSala->norte = NULL;
    novaSala->sul = NULL;
    novaSala->leste = NULL;
    novaSala->oeste = NULL;
    novaSala->chave = chave;
    return novaSala;
}


//Funcao que define a ligacao entre as salas do labirinto
void conectarSalas(Sala *origem, Sala *destino, char direcao) 
{
    switch (direcao) 
	{
        case 'N': origem->norte = destino; 
			break;
        case 'S': origem->sul = destino;
			break;
        case 'L': origem->leste = destino;
			break;
        case 'O': origem->oeste = destino;
			break;
    }
}

//Funcao para exibir a descricao da sala.
void exibirDescricao(Sala *sala) 
{
    printf("%s\n", sala->descricao);
}

//Funcao que verifica se todas as chaves forao coletadas no final do codigo.
int verificarChavesColetadas(int chaves[], int tamanho) 
{
    for (int i = 0; i < tamanho; i++) 
	{
        if (chaves[i] == 0) 
		{
            return 0;
        }
    }
    return 1;
}

//Exibe o Menu
char exibirMenu()
{
    char escolha;
    printf("- GOBIDARST -\n\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Reiniciar Jogo\n");
    printf("3. Sair\n\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &escolha);
    return escolha;
}

// Fun��o que retorna um n�mero aleat�rio entre min e max (inclusive)
int numeroAleatorioEntre(int min, int max) 
{
    return (rand() % (max - min + 1)) + min; //rand() % (max - min + 1) gera um n�mero entre 0 e (max - min). + min ajusta o intervalo para estar entre min e max.
}

//Som de chave sendo pega.
void somChave() 
{
    Beep(500, 100);
    Sleep(100);     
    Beep(600, 100); 
    Sleep(100);     
    Beep(700, 100); 
}

//Som Final Verdadeiro
void somFinal() 
{
    Beep(880, 200);
    Sleep(100);
    Beep(1100, 200);
    Sleep(100);
    Beep(1320, 200);
    Sleep(100);
    Beep(1760, 200);
    Sleep(100);
    Beep(2200, 200);
}

//Som cora��o
void somCoracao(int pausa, int repeticao) 
{
	for(int i = 0; i < repeticao; i++)
	{
		Beep(100, 100);
		Beep(100, 100);
		Sleep(pausa);
	}
}

int main() 
{	
	Sala *salas[43];
	char comando[10];
	int chaves[6] = {0};
	char escolha;
	int movimentos = 0;	
	
	//Cria��o das salas
	salas[0] = criarSala("Voce esta na entrada do que parece ser uma grande muralha antiga e robusta. Por algum motivo a sensacao de deja vu eh esmagadora.\nVoce consegue ver o formato de um ser com diversas pernas esculpido em marmore no portal de tal muralha.\nHa somente um caminho: para o NORTE.", 0);
	salas[1] = criarSala("Voce entrou pelo portal e a atmosfera parece estranhamente quieta, e a sensacao de desconforto eh gritante.\nVoce observa uma cidade ao NORTE. \nHa um portal de saida com uma estatua para o SUL\nVoce tambem consegue seguir a muralha pelo LESTE ou pelo OESTE.\n",0);
	salas[2] = criarSala("Voce anda alguns metros seguindo a muralha. \nA medida que voce anda, vai encontrando alguns destrocos do que parecem ser postos de patrulha abandonados.\nEntao voce encontra uma pequena brecha na parede da muralha pelo LESTE.\nOu voce pode voltar pela muralha pelo OESTE", 0);
	salas[3] = criarSala("Voce anda alguns metros seguindo a muralha.\nA medida que voce anda, mais e mais se torna dificil seguir a muralha por conta da quantidade anormal de arvores que vao surgindo.\nVoce entao se ve incapaz de seguir pelo oeste por conta de uma parede de pinheiros a sua frente.\nVoce avista uma catedral pelo NORTE.\nOu voce pode seguir muralha de volta pelo LESTE", 0);
	salas[4] = criarSala("Voce anda por algum tempo. A cada passo dado, seus instintos gritavam para voce retornar, algo naquele local nao parecia certo.\n Apos alguns minutos voce consegue chegar a centro da cidade. Voce procura por algum sinal de vida, mas sem sorte, a cidade estava deserta, como se o povo daquele local tivesse fugido as pressas.\nVoce avista o que parece ser uma biblioteca ao NORTE.\nAo OESTE consegue se ver uma catedral antiga.\nVoce tambem consegue seguir pelo SUL e voltar a entrada da muralha.", 0);
	salas[5] = criarSala("Voce se esgueira e entra pela brecha na parede. \nA atmosfera comeca a ficar cada vez mais claustrofobica. Mais e mais se torna dificil de avancar, e as paredes estao ficando cada vez mais estreitas. \nCom muita dificuldade voce consegue atravessar a grande brecha, mas se ve incapaz de voltar pelo caminho que veio.\n Dentro da muralha eh extremamente escuro, e a penumbra nao permite que voce enxergue de maneira significativa.\nVoce sente tocar em sua pele uma substancia viscosa, como se fossem grandes quantidades de teia de aranha. \nApesar da dificuldade, voce enxerga um tunel ao qual parece ter sido feito por uma especie de animal pelo SUL", 0);
	salas[6] = criarSala("Voce entra pelo tunel do animal. \nEh dificil se movimentar aqui, mas voce consegue avancar, descendo mais e mais pelo tunel.\nO cheiro dentro do tunel eh insuportavel, como se diversos restos de animais estivessem apodrecendo lentamente.\nVoce escuta um gotejamento estranho e constante, e tal liquido escorre pelo seu pescoco.\nVoce pode seguir pelo tunel em direcao ao OESTE.\nOu voce pode voltar pelo caminho que veio pelo NORTE.", 0);
	salas[7] = criarSala("Voce decide continuar seguindo pelo tunel.\nO caminho esta bloqueado pelo que parecem ser teias de aranha grossas, e a cada passo fica mais dificil de se movimentar. Ate que de repente voce escuta o que parecem ser ALGO se movimentando pelas paredes do grande tunel. \nMas ao andar alguns passos, voce finalmente encontra uma luz pelo que parece ser uma pequena saida.\nVoce pode sair pelo buraco ao OESTE e nao voltar.\n Ou retornar pelo tunel da criatura ao LESTE.", 0);
	salas[8] = criarSala("Voce chega ao que parece ser uma enorme e ameacadora catedral com um estilo gotico.\nEsta nao eh uma catedral comum, mas um monolito de pedra e trevas, um testemunho silencioso de uma era perdida.\nVoce pode adentrar a catedral pelo OESTE.\nIr para o centro da cidade pelo LESTE.\nOu seguir ate a muralha pelo SUL.", 0);
	salas[9] = criarSala("Voce entra na catedral abandonada.\nO som de gotas d'agua ecoa pelo vasto espa�o e a sensacao de solidao agora parecia mais evidente. \nUma enorme estatua da mesma criatura que a do portal abraca um RELOGIO sinistro com suas multiplas patas em cima de um altar onde pareciam ocorrer sacrificios.\nAo analisar a estatua, voce agora consegue identificar que tal criatura parecia possuir a cabeca de um animal semelhante a um bode ou carneiro.\nSeus olhos eram sem vida e ameacadores, como os de uma aranha. \nVoce olha pelo salao, ve varios bancos vazios e diversos simbolos os quais voce nao reconhece escritos nas paredes. \nDe repente um som estrondoroso ecoa pelo salao. Sua atencao retorna ao RELOGIO e voce percebe que o ponteiro comeca a se mover lentamente em direcao ao numero '50' manchado de vermelho. Algo naquele NUMERO lhe chama a atencao.\nVoce pode seguir uma porta para o que parece ser o patio pelo OESTE.\nSair da catedral pelo LESTE.\nOu entrar por uma porta atras do altar pelo NORTE.", 0);
	salas[10] = criarSala("Voce entra em uma biblioteca antiga.\nOs livros estao empoeirados e gastos, com excessao de um livro cujo a cor negra como a noite esta disposta em uma mesa no centro da sala.\nHa uma CHAVE em formato de um Querubim em cima do livro aberto, a qual voce imediatamente pega. Voce pode ler uma frase em destaque no livro:\n'GOBIDARST o Puro! GOBIDARST o Justo! GOBIDARST o Soberano! Devemos nossa vida a Ele e somente Ele!'\nVoce pode somente sair da biblioteca pelo SUL.", 1);
	salas[11] = criarSala("Voce entra pela porta atras do altar. O corredor eh iluminado somente com tochas com fogo azul\nDiversas estatuas humanas em poses como estivessem chorando guiam voce a uma porta adornada no fim do corredor.\nVoce pode entrar na porta adornada pelo NORTE.\nOu voce pode voltar ate a catedral pelo SUL.", 0);
	salas[12] = criarSala("Voce entra em um grande patio onde pareciam ser realizadas as meditacoes dos monges da catedral.\nO campo eh incrivelmente bem cuidado e passa uma estranha sensacao de paz e tranquilidade.\nMas tal tranquilidade eh cortada com um vulto se escondendo nos telhados. Voce decide seguir.\nVoce pode ir para a entrada do Mosteiro pelo SUL\nOu voltar para a catedral pelo LESTE.", 0);
	salas[13] = criarSala("Voce adentra o Mosteiro e avista um grande corredor com as portas escancaradas levando a quartos desarrumados.\nAo andar por alguns metros pelo Mosteiro, um quarto iluminado lhe chama a atencao.\nVoce pode entrar no quarto pelo OESTE\nOu voltar para o patio pelo NORTE.", 0);
	salas[14] = criarSala("Voce entra no que parece ser um vasto templo subterraneo. Duas estatuas de duas mulheres apontam para a esquerda e para a direita.\nO ambiente eh iluminado somente pelas tochas azuis, e diversas pilastras continuam pelo vasto corredor.\nVoce pode seguir o correor pelo LESTE ou OESTE.", 0);
	salas[15] = criarSala("Voce anda pelo vasto corredor ate chegar em uma parte que possui espelhos em ambos as paredes.\nTal disposicao de espelhos reflete a sua imagem infinitas vezes, o que te deixa desconfortavel.\nVoce pode seguir para o LESTE e entrar em uma passagem subterranea \nOu ir ate as duas estatuas pelo OESTE.", 0);
	salas[16] = criarSala("Voce anda pelo vasto corredor ate encontrar uma porta grande de madeira.\nAo entrar na tal porta voce chega em um grande salao adornado com ouro e marmore e um tapete vermelho guiando ate uma escada adornada.\nVoce pode subir a escada pelo OESTE\nOu entrar em uma porta ao SUL.", 0);
	salas[17] = criarSala("Ao entrar pela porta, voce enxerga uma grande sala de jantar vazia.\nHa uma grande mesa com diversas cadeiras desarrumadas, pratos e talheres jogados, e comida sujando o ambiente, como se um jantar tivesse sido interrompido.\nVoce encontra um buraco na parede onde antes havia um quadro pelo OESTE\nOu voce pode voltar ao salao pelo NORTE.", 0);
	salas[18] = criarSala("Ao adentrar no quarto iluminado, voce imediatamente avista uma silhueta humana manchada de sangue na parede, como um inseto esmagado.\nEm cima de uma cama esta uma CHAVE em formato de um Serafim a qual voce imediatamente pega. Do lado ha um bilhete ilumidado por uma vela com fogo azul que podia se ler:\n'Nao escute seus susurros! Quando nos perdemos a tal ponto? Por que somente eu consigo ver? Por que somente eu consigo ver? Por que-' O bilhete foi interrompido...\nVoce pode somente voltar ao Mosteiro pelo LESTE.", 1);
	salas[19] = criarSala("Voce anda e se encontra encontra catacumbas horrendas, o ar � �mido e o cheiro de mofo e sangue eh insuportavel.\nA medida que anda, consegue ver celas com diversas manchas e pedacos humanos. \nVoce observa os adornos das paredes e repara um local onde o padrao se quebra.\nO formato se assemelha a uma porta, ao encontar em tal retangulo, percebe-se a parede ranger e se mover um pouco: Uma passagem secreta.\nVoce pode seguir pela passagem secreta pelo SUL, mas sem certeza de retorno.\nIr para o corredor de espelhos pelo OESTE\nOu seguir as catacumbas pelo LESTE.", 0);
	salas[20] = criarSala("Voce se encontra em um corredor secreto dentro das paredes, parece que alguem espionava as pessoas por aqui.\nVoce pode entrar em uma passagem pelo SUL, mas parece ser dificil retornar...\nVoce pode tambem voltar para a sala de jantar pelo LESTE.\nOu voce pode sair por outro quadro mais a frente pelo NORTE.", 0);
	salas[21] = criarSala("Voce chega ao topo da escadaria. Pode se ver um grande quadro de um homem bem arrumado com os olhos negros como a noite.\nVoce consegue ver uma entrada por dentro do quadro levando ate o SUL\nOu voce pode seguir ate um corredor enxarcado com um liquido negro pelo NORTE.", 0);
	salas[22] = criarSala("Voce chega ao final das catacumbas encontrando diversos instrumentos de tortura largados pelo salao. \nEnxerga tambem escadas que levam ao que parece ser uma porta de metal mais acima\nVoce pode seguir pelas catacumbas pelo OESTE.\nOu subir as escadas pelo NORTE.", 0);
	salas[23] = criarSala("Voce entra em um quarto desarrumado do que parecia ser o laboratorio de um alquimista.\nDiversos grimorios estao dispostos em cima de mesas velhas de madeira...\nDiversos potes para manejar substancias...\nCom manchas de sangue, eram escritos simbolos e mais simbolos por toda a sala, e no centro uma palavra estranha: GOBIDARST.\nVoce pode entrar em um quarto pelo LESTE.\nAbrir uma porta de ferro e descer as escadas pelo SUL.\nEntrar em um quarto pelo NORTE.\nOu seguir para o lado de fora pelo OESTE.", 0);
	salas[24] = criarSala("Voce anda pelo corredor com um liquido negro. O cheiro de podridao permeia o ar.\nVoce consegue ir ate uma sala com um simbolo estranho na porta pelo LESTE.\nOu ir ate o topo das escadarias pelo SUL.", 0);
	salas[25] = criarSala("Voce se encontra no que parece ser uma sala totalmente destruida, as paredes sao compostas por teias de aranha e o mesmo liquido negro visto no corredor levando as escadarias. \nVoce consegue acessar um tunel liso e escorregadio que leva aos andares inferiores ao SUL\nOu seguir por um tunel que parece ter sido feito por algum tipo de animal pelo NORTE.", 0);
	salas[26] = criarSala("Voce anda em um patio com uma grama extremamente alta.\nVoce jura ouvir algo se movimentando pelo gramado. Mas mesmo assim continua avancando.\nVoce pode entrar em uma cabana pelo LESTE\nOu seguir ate o que parece ser uma pequena capela ao NORTE.", 0);
	salas[27] = criarSala("Voce entra em um quarto de uma pessoa que parecia estar fora de si.\nO cheiro era podre e o nome GOBIDARST se repetia de maneira bem mais significativa do que a sala anterior. Apesar da bagunca, voce identifica uma CHAVE em formato de Anjo manchada completamente com sangue em cima de uma escrivaninha, junto de uma faca e um bilhete escrito com sangue:\n'Nao deveis deixar o ignorante acessar o submundo junto dos SEIS servos. Assim ordena GOBIDARST, Assim ordena GOBIDARST.'", 1);
	salas[28] = criarSala("Voce entra em uma sala de jantar destruida, como se tivesse sido atacada por algum animal gigantesco. \nEh possivel avistar uma capela do lado de fora a partir de um rombo na parede ao OESTE\nOu ir para o laboratorio pelo SUL.", 0);
	salas[29] = criarSala("Voce anda pelos tuneis da criatura.\nAo chegar no final, voce se ve em uma caverna ampla com agua escorrendo pelas paredes e formando um grande lago no centro.\n Voce pode seguir por um grande Portal com simbolos escritos com uma substancia negra pelo NORTE\n Ou seguir pelos tuneis da criatura pelo SUL.", 0);
	salas[30] = criarSala("Voce entra em uma pequena e macabra capela.\n Pode se enxergar um grande buraco no chao levando a uma passagem subterranea. Ha teias de aranha enormes cobrindo as paredes junto de um liquido negro viscoso.\nVoce pode entrar pelo buraco ao NORTE. \nExplorar um matagal fora da capela pelo SUL.\nOu entrar em uma pequena cabana por um rombo pelo LESTE.", 0);
	salas[31] = criarSala("Voce agora se encontra em um corredor escuro, iluminado somente por uma luz vermelha vindo da fresta das paredes.\nAlgo naquele corredor nao parecia deste mundo, era como adentrar o submundo.\nVoce pode seguir o corredor pelo OESTE\nVoce pode entrar por um buraco estreito pelo LESTE, mas o caminho de volta parece ser dificil de fazer.\nOu voltar para caverna pelo SUL.", 0);
	salas[32] = criarSala("Voce esta em uma sala redonda. \nO chao possui um vidro que projeta uma luz carmesim no teto, revelando uma imagem de pessoas sofrendo em um purgatorio eterno comandandado por uma criatura de varias pernas.\nVoce sente que o seu destino pode ser decidido com a proxima escolha:\nVoce pode seguir pelo NORTE, adentrando uma enorme porta adornada com a mesma criatura vista diversas vezes.\nOu entrar em uma fresta preenchida com um liquido negro na parede pelo SUL, a qual parece nao ter mais volta.", 0);
	salas[33] = criarSala("Voce entra no que parece ser uma toca de aranha gigante. Um calafrio te domina, e voce fica enojado com o ambiente. \nO cheiro podre, por conta da quantidade enorme de cadaveres, permeia a sala, o que torna dificil de respirar.\nVoce ve diversos casulos pendurados em toda a sala envoltos pela mesma gosma negra vista anteriormente. Os casulos parecem se mecher.\nAo fundo voce enxerga uma porta com ENTRADAS PARA CHAVES, cujo o acesso parece ter sido propositalmente protegido com a quantidade enorme de teias.", 0);
	salas[34] = criarSala("Voce adentra uma caverna enorme, com diversos ossos humanos espalhados pelo chao e paredes.\nO cheiro eh horrendo. Ha diversos buracos no teto, que escorrem um liquido negro viscoso.\nParece que eh aqui que a criatura se alimenta...\nEu posso seguir pela caverna pelo NORTE.\nOu sair dela pelo SUL.", 0);
	salas[35] = criarSala("Voce adentra a caverna e imediatamente eh envolvido por uma atmosfera sombria e opressiva.\n O chao rochoso esta marcado por inumeras garras, algumas tao profundas que quase atravessam a pedra. \nSimbolos arcanos adornam as paredes, contando a historia de batalhas antigas travadas neste lugar entre uma criatura e os exercitos celestiais.\nVoce pode voltar para a toca da criatura pelo SUL.\nSeguir o som de agua pelo LESTE\nOu seguir flores brancas pelo OESTE.", 0);
	salas[36] = criarSala("A beira de um lago profundo, voce avista estatuas de anjos Tronos que foram derrotados pela criatura.\n As aguas do lago guardam segredos sombrios e memorias dolorosas dos que foram vencidos.\n Voce ve uma passagem pela augua pelo LESTE, mas sem certeza de retorno\n Ou voce pode voltar para a caverna com simbolos pelo OESTE.", 0);
	salas[37] = criarSala("Neste espa�o sombrio, flores palidas crescem em meio a escurid�o.\nAs petalas brancas das flores parecem tingidas de tristeza, simbolizando os anjos que ca�ram diante do poder de criatura. \nVoce pode seguir uma luz pelo NORTE \nOu ir para o campo de batalha pelo LESTE.", 0);
	salas[38] = criarSala("Voce entra em um vale onde estatuas dos principados olham para o ceu, como se aguardassem por redencao ou por um sinal de seus lideres celestiais.\nEste lugar � um testemunho silencioso da queda dos pr�ncipes celestiais que um dia protegeram estas terras, agora abandonadas a escuridao.\nVoce pode ir ao vale de flores pelo SUL\nOu voce pode seguir um hino suave ao OESTE.", 0);
	salas[39] = criarSala("Depois de nadar por uma passagem subaquatica estreita e fria, voc� emerge em uma c�mara vasta e sombria.\nA agua goteja das paredes rochosas, criando um som constante e hipnotico que ecoa por todo o ambiente. \nNo centro da sala, sobre um pedestal de pedra envelhecida e coberta de musgo, esta uma chave com o formato de um anjo Trono a qual voce imediatamente pega. \nA chave emana uma aura sutil de luz, contrastando com a escurid�o ao redor.\nAo olhar para as paredes, voce consegue ler escritas em hebraico contando a respeito da vinda dos anjos a Gileade e sucumbindo para a escuridao absoluta de GOBIDARST.\nVoce pode voltar pelo tunel sub-aquatico pelo OESTE.", 1);
	salas[40] = criarSala("Seguindo um hino suave, voce adentra um corredor.\nVoce eh envolvido pelos ecos dos hinos angelicais que ainda ressoam pelas paredes.\nCada passo reverbera como uma homenagem a gl�ria que uma vez preencheu estas terras, agora silenciadas por uma presen�a opressiva.\n\nA medida que avan�a, voce se depara com uma bifurca��o no caminho. Os ecos dos hinos tornam-se mais intensos, quase ensurdecedores, dificultando a tomada de decisao.\nVoce deve se seguir pelo instinto: SUL ou OESTE.", 0);
	salas[41] = criarSala("Voce adentra um salao redondo completamente iluminado.\nVoce olha para o teto e enxerga uma pintura de um ceu azul com diversos tipos de anjos voando.\nNo centro da sala voce encontra uma chave em formato de Arcanjo, a qual voce imediatamente pega.\n Ha uma porta gigantesca com a seginte frase no topo: 'NAO TENHA MEDO'.\Voce pode adentrar a porta pelo SUL.\nOu voltar por onde veio pelo LESTE.", 1);
	salas[42] = criarSala("Ao entrar na galeria, o ar frio e estagnado te envolve, um sussurro de misterios antigos.\nAs pinturas que adornam as paredes sao homenagens macabras a entidade que uma vez governou este lugar. \nCada tela eh um portal para uma visao perturbadora, onde anjos caidos veneram a criatura disfarcada, suas asas quebradas formando um coro sombrio ao redor do falso sacerdote.\nNo centro da sala consegue se ver uma chave em formato de um anjo Principado, a qual voce coleta.", 1);
	
	//Conex�es entre as salas
	conectarSalas(salas[0], salas[1], 'N');
	conectarSalas(salas[1], salas[0], 'S');
	conectarSalas(salas[1], salas[2], 'L');
	conectarSalas(salas[1], salas[3], 'O');
	conectarSalas(salas[1], salas[4], 'N');
	conectarSalas(salas[2], salas[1], 'O');
	conectarSalas(salas[2], salas[5], 'L');
	conectarSalas(salas[5], salas[6], 'S');
	conectarSalas(salas[6], salas[5], 'N');
	conectarSalas(salas[6], salas[7], 'O');
	conectarSalas(salas[6], salas[7], 'O');
	conectarSalas(salas[7], salas[6], 'L');
	conectarSalas(salas[7], salas[0], 'O');
	conectarSalas(salas[3], salas[8], 'N');
	conectarSalas(salas[3], salas[1], 'L');
	conectarSalas(salas[8], salas[3], 'S');
	conectarSalas(salas[8], salas[4], 'L');
	conectarSalas(salas[4], salas[1], 'S');
	conectarSalas(salas[4], salas[8], 'O');
	conectarSalas(salas[4], salas[10], 'N');
	conectarSalas(salas[10], salas[4], 'S');
	conectarSalas(salas[8], salas[9], 'O');
	conectarSalas(salas[9], salas[12], 'O');
	conectarSalas(salas[12], salas[9], 'L');
	conectarSalas(salas[12], salas[13], 'S');
	conectarSalas(salas[13], salas[12], 'N');
	conectarSalas(salas[13], salas[18], 'O');
	conectarSalas(salas[18], salas[13], 'L');
	conectarSalas(salas[9], salas[11], 'N');
	conectarSalas(salas[9], salas[8], 'L');
	conectarSalas(salas[11], salas[9], 'S');
	conectarSalas(salas[11], salas[14], 'N');
	conectarSalas(salas[14], salas[11], 'S');
	conectarSalas(salas[14], salas[15], 'L');
	conectarSalas(salas[14], salas[16], 'O');
	conectarSalas(salas[16], salas[14], 'L');
	conectarSalas(salas[16], salas[17], 'S');
	conectarSalas(salas[16], salas[21], 'O');
	conectarSalas(salas[17], salas[16], 'N');
	conectarSalas(salas[17], salas[20], 'O');
	conectarSalas(salas[20], salas[17], 'L');
	conectarSalas(salas[20], salas[18], 'S');
	conectarSalas(salas[20], salas[21], 'N');
	conectarSalas(salas[21], salas[20], 'S');
	conectarSalas(salas[21], salas[42], 'O');
	conectarSalas(salas[21], salas[24], 'N');
	conectarSalas(salas[42], salas[21], 'L');
	conectarSalas(salas[24], salas[21], 'S');
	conectarSalas(salas[24], salas[25], 'L');
	conectarSalas(salas[25], salas[24], 'O');
	conectarSalas(salas[25], salas[16], 'S');
	conectarSalas(salas[25], salas[29], 'N');
	conectarSalas(salas[29], salas[25], 'S');
	conectarSalas(salas[29], salas[31], 'N');
	conectarSalas(salas[31], salas[29], 'S');
	conectarSalas(salas[31], salas[34], 'L');
	conectarSalas(salas[31], salas[32], 'O');
	conectarSalas(salas[32], salas[31], 'L');
	conectarSalas(salas[32], salas[24], 'S');
	conectarSalas(salas[32], salas[33], 'N');
	conectarSalas(salas[15], salas[14], 'O');
	conectarSalas(salas[15], salas[19], 'L');
	conectarSalas(salas[19], salas[15], 'O');
	conectarSalas(salas[19], salas[10], 'S');
	conectarSalas(salas[19], salas[22], 'L');
	conectarSalas(salas[22], salas[19], 'O');
	conectarSalas(salas[22], salas[23], 'N');
	conectarSalas(salas[23], salas[22], 'S');
	conectarSalas(salas[23], salas[27], 'L');
	conectarSalas(salas[27], salas[23], 'O');
	conectarSalas(salas[23], salas[26], 'O');
	conectarSalas(salas[23], salas[28], 'N');
	conectarSalas(salas[26], salas[23], 'L');
	conectarSalas(salas[26], salas[30], 'N');
	conectarSalas(salas[28], salas[23], 'S');
	conectarSalas(salas[28], salas[30], 'O');
	conectarSalas(salas[30], salas[26], 'S');
	conectarSalas(salas[30], salas[28], 'L');
	conectarSalas(salas[30], salas[34], 'N');
	conectarSalas(salas[34], salas[30], 'S');
	conectarSalas(salas[34], salas[35], 'N');
	conectarSalas(salas[35], salas[36], 'L');
	conectarSalas(salas[36], salas[35], 'O');
	conectarSalas(salas[35], salas[34], 'S');
	conectarSalas(salas[35], salas[37], 'O');
	conectarSalas(salas[37], salas[35], 'L');
	conectarSalas(salas[37], salas[38], 'N');
	conectarSalas(salas[38], salas[37], 'S');
	conectarSalas(salas[38], salas[40], 'O');
	conectarSalas(salas[40], salas[38], 'L');
	conectarSalas(salas[36], salas[39], 'L');
	conectarSalas(salas[39], salas[36], 'O');
	conectarSalas(salas[40], salas[41], 'O');
	conectarSalas(salas[40], salas[0], 'S');
	conectarSalas(salas[41], salas[40], 'L');
	conectarSalas(salas[41], salas[33], 'S');
	
	Sala *salaAtual = salas[0];
	
	while (1)
    {
    	system("cls");
		escolha = exibirMenu();

		if(escolha == '1')
		{   
		    //Loop principal do jogo
		    while (1)
			{
		        system("cls"); //Apaga o terminal toda a vez que define um destino.
		        exibirDescricao(salaAtual);//Chama a funcao para exibir a descricao.
		        if (salaAtual == salas[33]) //Condicao para ativar o final do jogo.
				{
		            if (verificarChavesColetadas(chaves, 6) == 1)  //Condicao para o final verdadeiro do jogo.
					{
						somFinal();
		                printf("\nVoce sente uma presenca atras de voce, uma luz radiante e acolhedora.\n Com as seis chaves em maos, voce as insere nas fechaduras do portal diante de voce.\n Uma intensa luz dourada emana do portal, iluminando as terras ao redor e dissipando todas as trevas.\nSua ultima memoria e de uma paz profunda enquanto voce atravessa o portal, libertando a luz nas terras sombrias.\nVoce conquistou o final 'Enviado de Deus'!\nObrigado por Jogar!");
		            } 
					else 
					{
						Beep(500, 1000);
		                printf("\nVoce sente uma presenca atras de voce, a imponencia de tal te faz ficar paralisado.\nA sua ultima memoria eh ser abracado por diversas maos humanas e pilhas de dentes se fechando em seu pescoco.\nVoce conquistou o final 'Abrace o Submundo'.\Tente achar todas as chaves e conquistar o final verdadeiro!");
		            }
		            
		            salaAtual = salas[0]; //Define a sala atual como 0 novamente.
            		memset(chaves, 0, sizeof(chaves)); //Reseta as chaves.
           			movimentos = 0; //Reseta os movimentos.
		    		getch();
		            break;
		        }
		        
		        //Eventos do Monstro Maligno das Trevas Trevosas
		        if(movimentos == numeroAleatorioEntre(1, 10))
		        {
		        	somCoracao(1000, 4);
		        	printf("Voce sente ser observado...\nAo olhar para o LESTE, voce jura ter visto um vulto passar por voce rapidamente.\n");
				}
				if(movimentos == numeroAleatorioEntre(11, 20))
		        {
		        	somCoracao(900, 6);
		        	printf("Voce escuta algo se aproximando por tras de voce...\n Ao olhar para o tras, voce somente ve diversas pegadas parecidas indo em direcao ao OESTE.\n");
				}
				if(movimentos == numeroAleatorioEntre(21, 30))
		        {
		        	somCoracao(800, 8);
		        	printf("Voce sente uma gota morna cair em sua testa...\n Ao olhar para o cima, voce ve uma enorme goteira de um liquido negro escorrer do teto em direcao ao SUL.\n Parecia recente.\n");
				}
				if(movimentos == numeroAleatorioEntre(31, 40))
		        {
		        	somCoracao(700, 10);
		        	printf("Voce sente uma respiracao pesada em seu pescoco...\n Ao se virar,E voce enxerga uma cabeca de carneiro te observando de um canto escuro ao NORTE.\n");
				}
				if(movimentos == numeroAleatorioEntre(41, 50))
		        {
		        	somCoracao(0, 20);
		        	printf("Voce escuta um grunhido alto vindo do OESTE...\nAo se virar para a origem do ruido, uma aranha gigante com cabeca de carneiro, olhos escuros e patas que pareciam bracos humanos fica te encarando por longos segundos.\nEla abre um longo sorriso antes de sair correndo de volta de onde veio.\n");
				}
		        if(movimentos == numeroAleatorioEntre(51, 60))
		        {
		        	Beep(500, 1000);
		        	printf("Voce escuta sinos tocando da direcao da CATEDRAL...\nDe repente o ar fica gelado, suas maos imediatamente ficam tremulas...\nVoce sente algo encostar em suas costas, como se fossem pelos. Voce olha pra cima e ve dois grandes olhos negros te encarando.\n Sua ultima memoria eh ser envolto de teias de aranha e seus pulmoes sendo preenchidos com um liquido negro.\nFim de jogo.");
		        	salaAtual = salas[0]; //Define a sala atual como 0 novamente.
            		memset(chaves, 0, sizeof(chaves)); //memset � uma fun��o que preenche um bloco de mem�ria com um valor especifico: No caso pega o inicio do vetor chave, e posiciona com o valor 0 todas as casas do mesmo pegando seu tamanho.
            		movimentos = 0; //Reseta os movimentos.
		        	getch();
		        	break;
				}
		        
		        //Salas com chaves:
		        if (salaAtual == salas[10]) 
				{
					somChave();
		            chaves[0] = 1;//Adiciona uma chave no vetor chave.
		            printf("Voce coletou a chave Querubim.\n");
		        } 
				if (salaAtual == salas[18]) 
				{
					somChave();
		            chaves[1] = 1;
		            printf("-> Voce coletou a chave Serafim.\n");
		        }
				if (salaAtual == salas[27]) 
				{ 
					somChave();
		            chaves[2] = 1;
		            printf("-> Voce coletou a chave Anjo.\n");
		        }
				if (salaAtual == salas[39]) 
				{
					somChave();
		            chaves[3] = 1;
		            printf("-> Voce coletou a chave Trono.\n");
		        }
				if (salaAtual == salas[42]) 
				{ 
					somChave();
		            chaves[4] = 1;
		            printf("-> Voce coletou a chave Principado.\n");
		        }
				if (salaAtual == salas[41]) 
				{ 
					somChave();
		            chaves[5] = 1;
		            printf("-> Voce coletou a chave Arcanjo.\n");
		        }
		        
		        printf("Digite a direcao (N, S, L, O) ou 'M' para voltar ao menu: "); //Movimentos do jogo.
		        scanf("%s", comando); //Le o input do usuario
				
				
				for (int i = 0; comando[i]; i++) 
				{
		        	comando[i] = toupper(comando[i]);
		    	}
		    	
		        if (strcmp(comando, "M") == 0) 
				{
		            printf("Voltando ao Menu...\n");
		            getch();
		            break;
		        }
		
				//Validar movimentacao
		        int movimentoValido = 1;
		        
		        if (strcmp(comando, "N") == 0) //String Compare compara duas strings, se ambas forem iguais, retorna 0.
				{
		            if (salaAtual->norte != NULL) {
		                salaAtual = salaAtual->norte; //Define a sala atual como a sala "ao norte" da mesma, definido anteriormente.
		                movimentos++; //Aumenta o numero de movimentos.
		            } 
					else 
					{
		                movimentoValido = 0;
		            }
		        } 
				else if (strcmp(comando, "S") == 0) 
				{
		            if (salaAtual->sul != NULL) 
					{
		                salaAtual = salaAtual->sul;
		                movimentos++;
		            } 
					else 
					{
		                movimentoValido = 0;
		            }
		        } 
				else if (strcmp(comando, "L") == 0) 
				{
		            if (salaAtual->leste != NULL) 
					{
		                salaAtual = salaAtual->leste;
		                movimentos++;
		            } 
					else 
					{
		                movimentoValido = 0;
		            }
		        } 
				else if (strcmp(comando, "O") == 0) 
				{
		            if (salaAtual->oeste != NULL) 
					{
		                salaAtual = salaAtual->oeste;
		                movimentos++;
		            } 
					else 
					{
		                movimentoValido = 0;
		            }
		        } 
				else 
				{
		            printf("Comando invalido. Tente novamente.\n");
		            movimentoValido = 0;
		        }
		
		        if (!movimentoValido) 
				{
		            printf("Movimento invalido\n");
		            getch(); 
		        }
		    }
		}
		
		else if (escolha == '2') // Reiniciar Jogo
        {
        	printf("Reiniciando o jogo...\n");
			salaAtual = salas[0]; //Define a sala atual como 0 novamente.
            memset(chaves, 0, sizeof(chaves)); //Reseta as chaves.
            movimentos = 0; //Reseta os movimentos.
			getch();
        }
        else if (escolha == '3') // Sair do jogo
        {
            printf("Saindo do jogo...\n");
		    
			//Libera o uso das salas na memoria.
			for (int i = 0; i < 42; i++) 
			{
	   	 		free(salas[i]);
			}
            break;
        }
        else
        {
            printf("Opcao invalida. Tente novamente.\n");
            getch();
        }
    }
    return 0;
}


