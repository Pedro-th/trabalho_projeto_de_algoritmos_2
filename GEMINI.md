# Diretrizes Gerais e Regras de Conduta para o Desenvolvimento

Este workspace segue estritamente as diretrizes abaixo durante todo o ciclo de desenvolvimento:

## 1. 🛑 Planejamento Obrigatório e Aprovação Prévia (Approval Gate)
- **Elaboração de Plano**: Antes de realizar qualquer alteração no código (seja nova funcionalidade, refatoração, melhoria de layout ou correção de bug), elabore primeiramente um **Plano de Implementação Detalhado** descrevendo as alterações propostas, impacto e plano de testes.
- **Aprovação do Usuário**: **PARE e aguarde a confirmação/aprovação explícita do usuário** antes de aplicar qualquer alteração nos arquivos de código.
- **Exceção**: Apenas pequenos ajustes finos ou correções imediatas de código feito na mesma sessão dispensam a criação de um novo plano.

## 2. 🎯 Limitação Estrita de Escopo
- **Foco Exclusivo**: Altere estritamente os arquivos e trechos de código diretamente relacionados à solicitação atual.
- **Sem Modificações Acessórias**: Não altere formatações, nomenclaturas, variáveis, textos ou estruturas que não foram solicitadas.
- **Preservação de Código**: Mantenha intacta qualquer lógica adjacente ou código legado que não necessite de modificação.

## 3. 🌿 Git Flow, Branches e Política de Commits
- **Estrutura de Branches**:
  - `main`: Produção estável. Nunca recebe commits diretos ou merges precipitados.
  - `homologation`: Ambiente de homologação e desenvolvimento ativo.
  - As branches `main` e `homologation` não se cruzam diretamente de forma arbitrária.
- **Feature Branches**:
  - Toda nova alteração é desenvolvida a partir de `homologation` em uma branch dedicada (ex.: `feat/<nome>`, `fix/<nome>`, `docs/<nome>`).
  - Ao finalizar a tarefa, a branch é mergeada conforme fluxo e podada (removida).
- **Política Rígida de Commits**:
  - **Proibição de Commit/Push Automático**: NUNCA execute `git commit` ou `git push` de forma automática.
  - **Commits Atômicos**: Separe as mudanças em commits pequenos e bem contextualizados.
  - **Recomendação de Comandos**: A IA deve sugerir o comando exato em **Português do Brasil** no formato convencional (ex.: `git commit -m "feat: adicionar controle de permissões por perfil"`).
  - Executar o commit SOMENTE se o usuário solicitar expressamente (ex.: *"pode commitar"*, *"faça o commit"*).

## 4. 🔒 Segurança, LGPD e Gestão de Segredos
- **LGPD (Lei Geral de Proteção de Dados)**:
  - Todo e qualquer desenvolvimento deve seguir rigorosamente as regras da LGPD (minimização de dados, consentimento, privacidade por design).
  - Dados sensíveis devem ser protegidos e nunca expostos em logs públicos ou mensagens de erro.
- **Validação de .gitignore e .env**:
  - Validar ativamente para garantir que nenhuma credencial, token ou arquivo de ambiente vaze para o repositório.

## 5. 🗄️ Atualização e Impacto no Banco de Dados
- Toda alteração no sistema precisa passar por uma análise prévia de impacto no banco de dados.
- Caso haja impacto, criar as devidas migrations e estruturas seguindo as melhores práticas oficiais de PostgreSQL e Supabase (RLS, tipos seguros, índices adequados).

## 6. 🎨 Design System, Padronização de UI e Consistência Visual
- **Padrão Anti-Slop**: Interfaces com acabamento premium, visual intencional e sem vícios de IA, utilizando `taste-skill`, `ui-ux-pro-max`, `shadcn` e `web-design-guidelines`.
- **Validação Cruzada de UI**: Sempre que a estrutura visual ou padrão de um componente for atualizado, audite e replique a consistência nas demais telas, rotas e cards. Mapeie e anote os padrões visuais adotados.

## 7. 📚 Documentação Contínua e Pasta `docs/`
- Centralizar a documentação do projeto na pasta `docs/` (arquitetura, roadmap, catálogo de componentes, stack).
- Ao finalizar qualquer funcionalidade, tela, rota ou alteração de comportamento, atualize a documentação correspondente antes de dar a tarefa por encerrada.

## 8. 🧠 Uso Ativo das Skills do Workspace
- Utilizar intensivamente as skills instaladas em `.agents/skills/`:
  - `planning-with-files`: Manter planos e acompanhamento de progresso em arquivos `.md`.
  - `superpowers`: Metodologia rigorosa (TDD, debugging metódico, verificação antes de entrega).
  - `supabase` e `supabase-postgres-best-practices`: Para modelagem e segurança do banco.
  - Skills de UI/UX (`shadcn`, `ui-ux-pro-max`, `taste-skill`, `frontend-design`, `web-design-guidelines`): Para identidade visual e acessibilidade.

## 9. ✅ Validação e Verificação Antes da Conclusão
- Antes de considerar qualquer tarefa finalizada, execute os comandos de verificação/compilação local (build, testes, linter, TypeScript check) para garantir ausência de erros e regressões.
