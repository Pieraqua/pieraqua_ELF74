Respostas das perguntas no item 6:

1.Onde aparecem as mensagens enviadas via cout?

-> Aparecem no Terminal I/O dentro do próprio Workbench.

2.Como entrar dados para leitura via cout?

-> No Terminal I/O embutido na IDE, há um espaço para entrada de dados indicado por "input"

3.Quais os valores dos símbolos pré-definidos que você apresentou? O que significam?

-> __cplusplus: apresenta um valor para a versão da linguagem C++ sendo utilizada. No caso, 201703 representa a versão C++ 17. Ex: 201703.

  __DATE__: Apresenta o dia em que foi rodado o código na máquina/processador, no formato "Mês dia ano". Ex: Aug 19 2022.

  __TIME__: Apresenta o horário em que foi rodado o código na máquina/processador, no formato "Hora:Minutos:Segundos". Ex: 15:40:40.

  __FILE__: Apresenta o endereço do arquivo sendo rodado no formato de uma string constante em C. Ex: C:\CWS41\pieraqua_ELF74\Lab1\main.
  cpp.
  __LINE__: Apresenta a linha atual, i.e., a linha em que se encontra essa macro. Ex: 104.

  __STDC__: Apresenta valores para indicação de operação normal. Geralmetne é esperado valor 1, sendo sempre 1 para arquivos de usuário. Ex: 1.

  __STDC_VERSION__: Apresenta o número de versão do C sendo utilizado no formato yyyymmL, em que yyyy representa o ano e mm representa o mês da versão Standard. Ex: 201710.

  __ARM_ARCH: Apresenta a versão da arquitetura do micro. Ex: 7.

  __ARM_ARCH_ISA_THUMB: Apresenta valor 1 se o núcleo suporta a o conjunto de instruções T32 original ou 2 se suporta o conjunto de instruções T32 nas arquiteturas v6T2 e v7. Ex: 2.

  _ARM_SIZEOF_MINIMAL_ENUM: Apresenta o tipo de menor enumeração. Pode ser 1 ou 4, dependendo se "fshorts-enums" estiver especificado ou não. Ex: 1.

  __ARM_SIZEOF_WCHAR_T: Apresenta o tamanho de wchar em bytes. Tem valor 2 se "-fshort-wchar" estiver especificado e 4 se "-fno-short-wchar" estiver especificado. Ex: 4.

  __ARMVFP__: Inteiro definido baseado na opção "--fpu" e que indica se instruções ponteiro de float foram definidas. Ex: 4.

  __CORE__: Inteiro que identifica o chip em uso. Valor reflete a configuração de "--cpu". Ex: 13.

4.Que tipo de instrução assembly foi usada para a soma dos dois valores float ?
Qual configuração do projeto no IAR causou o uso desta instrução ?

->Foi utilizada uma função indicada por "__aeabi_dadd", em que são somados dois valores do tipo double. Foi feita uma transformação de float para double por meio de "__aeabi_f2d" antes e "__aeabi_d2f" de double para float ao final.

->A configuração que causou o uso dessa instrução foi o FPU em "VFPv4 single precision". Isso fez com que fosse utilizado um método de 32-bits para que fosse obtida uma melhor precisão do que com somente float. No caso, provavelmente a IEEE 754-2019 Format.