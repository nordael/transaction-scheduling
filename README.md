# Implementação dos algoritmos de teste de equivalência por visão e serialibidade por conflito
Esse projeto foi feito para a disciplina de Bancos de Dados,utilizando a linguagem C e makefile para compilação. 

## Compilação 
Compila a partir do C, utilizando comandos make.  
Para efetuar a compilação, basta e digitar make.
Para excluir todos os arquivos temporários digite make clean,
e para excluir temporários e o executável digite make purge.  
Ao compilar criará um arquivo executável com o nome escalona.

## Execução 
# Entrada
Leitura dos comandos por linha separados por quatro campos, _tempo cheagada_,_id da transação_,_operação_,_atributo em que ocorre o comando_, através da entrada padrão (stdin). 

# Saída
A saída ocorre através da saída padrão, sendo que cada linha é composta por um escalonamento do agendamento recebido, sendo representado por 4 campos:  
(_identificador do escalonamento_,_lista de transações_,_serialidade do escalonamento_,_equivalência do escalonamento por visão_). 

# Algoritmo de equivalência por visão
Utiização de função auxiliares, para efetuar as permutações das transações por meio de adaptações no algoritmo de permutação por backtracking. As permutações são traduzidas para apenas aquelas em que não ocorre mudança na order dos comandos em uma mesma transação.

# Algoritmo de seriação de conflito
Utiliza um algoritmo baseado em busca em profundidade sobre um grafo para detectar se existe um ciclo no mesmo. O grafo é construido criando arestas direcionadas (dependências) entre os vertices (transações) de acordo com as operações efetuadas por transações num agendamento. 

## Autor 
Rubens Zandomenighi Laszlo e Julio L. Martins 
