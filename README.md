# Controle de Dados da Tabela Brasileira de Composição de Alimentos (RA2)

Projeto prático desenvolvido para a disciplina de **Programação Imperativa** da PUCPR (Prof. Alcides Calsavara).

---

## 👥 Divisão das Tarefas da Equipe

| Integrante | Cor no PDF | Módulo / Responsabilidade | Status |
| :--- | :---: | :--- | :---: |
| **Vini** | 🔵 Azul | Transcrição de dados, criação do binário (`dados.bin`), listas ligadas ordenadas e geração das árvores binárias | ✅ Concluído |
| **Kulik** | 🟢 Verde | Front-End: Opções 1 (Categorias), 2 (Alimentos) e 3 (Energia Decrescente via Árvore) | ⏳ A preencher |
| **Guilherme** | ⚪ Cinza | Front-End: Opções 4 (Proteína Decrescente via Árvore), 5 (Faixa Energia via Árvore) e 6 (Faixa Proteína via Árvore) | ✅ Concluído |
| **Carol** | 🟠 Laranja | Front-End: Opções 7 (Remover Categoria), 8 (Remover Alimento) e 9 (Sair e Salvar `dados.bin`) | ⏳ A preencher |

---

## 🏛️ Estrutura de Arquivos

```text
├── .vscode/                 # Tasks de compilação automática no VS Code
├── Back/
│   ├── C/
│   │   ├── alimento.h / alimento.c   # Enum e struct Alimento, conversões
│   │   ├── P1/                       # Conversor CSV -> dados.bin
│   │   └── P2/                       # Programa principal em memória
│   │       ├── p2.c                  # Função main isolada do P2
│   │       ├── categorias_lista/     # Lista simplesmente encadeada de categorias
│   │       ├── alimentos_lista/      # Lista encadeada de alimentos
│   │       ├── arvore_energia/       # Árvore binária indexada por Kcal
│   │       └── arvore_proteina/      # Árvore binária indexada por gramas de proteína
│   └── Dados/
│       ├── alimentos.csv             # Base textual
│       └── dados.bin                 # Base binária gerada
└── Front/
    ├── front.h                       # Protótipos das funções do menu e opções 1 a 9
    └── front.c                       # Menu em loop no terminal + Opções 4, 5 e 6 implementadas
```

---

## 📋 Regras de Implementação Seguidas (Prof. Alcides)
1. **Sem `break` ou `continue`**: Loops controlados estritamente por flags booleanas.
2. **Retorno Único**: Preferencialmente apenas um `return` por função.
3. **Documentação**: Funções e variáveis com nomenclatura significativa e comentários detalhados.
4. **Main Isolada**: `p2.c` contém exclusivamente a inicialização e chamada da interface.

---

## 🚀 Como Compilar e Executar

### Opção 1: Via VS Code
Pressione `Ctrl + Shift + B` e selecione **Compilar Projeto P2**.

### Opção 2: Via Terminal (GCC)
A partir da pasta raiz do repositório:
```bash
gcc -Wall -Wextra -std=c11 -g3 Back/C/P2/p2.c Back/C/P2/categorias_lista/categorias_lista.c Back/C/P2/alimentos_lista/alimentos_lista.c Back/C/P2/arvore_energia/arvore_energia.c Back/C/P2/arvore_proteina/arvore_proteina.c Back/C/alimento.c Front/front.c -o Back/C/P2/output/p2.exe

./Back/C/P2/output/p2.exe
```
