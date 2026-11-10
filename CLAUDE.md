@AGENTS.md

# Claude Code only

Claude Code loads `AGENTS.md` only through the import above (a `CLAUDE.md`
exists, so the automatic fallback is off). Keep that line first.

## Workflow

- **The main session** (Opus 5.5) talks with the user, plans and reviews. It writes
  `.claude/plans/<feature>.md`: goal, files to touch, constraints, a checklist of
  steps, and how to verify each one.
- **`scanner`** (Haiku): read-only search and summaries. Use it for raw reading
  before planning (this repo, the sibling repo, vial-gui / vial-qmk sources), so
  the main session keeps only the findings.
- **`executor`** (Sonnet): carries out the plan, commits after each step.
- **DeepSeek via opencode**: cheap executor for well-scoped steps — skill
  `opencode-delegation`.
- At the end, the main session reviews the diff against the plan before
  reporting done.
- Briefs for subagents and sessions point to the `AGENTS.md` sections to read
  (`Checks`, `Never`) and ask for a list of what they noticed but did not fix;
  worthwhile items go to `docs/BACKLOG.md` (create it if missing).
- Large independent pieces (one per area or per plan step) can run as parallel
  sessions sharing the folder, each owning a disjoint set of files; the main
  session commits after reviewing. Cross-cutting reading (merging, summarizing many
  files) goes to a Sonnet subagent so the main context keeps only the result.

## Desktop app traps

- Subagent definitions load from the **main checkout's** `.claude/agents/`
  (the app passes `--project-config-root` = the main repo), not from a
  worktree: a new or changed agent works only once it is on `main`. Skills and
  `CLAUDE.md` do load from the worktree.
- A turn started by another session's completion cannot start new sessions;
  start the next wave on a user turn, or ahead of time.

## Model and effort per role

The user approves these levels; pass them explicitly (`effort` on the Agent
call or on a started session).

| Role | Model | Effort |
|---|---|---|
| Main session: planning, review, writing `AGENTS.md` | Opus 5.5 | high |
| Main session: quick questions with the user | Opus 5.5 | medium |
| `scanner` | Haiku | medium (frontmatter default) |
| `executor`, routine planned step | Sonnet | medium (frontmatter default) |
| `executor`, hard step (tricky logic, cross-file, subtle bugs) | Sonnet | high |
| Doc-writing / verification sessions | Sonnet | high |
| DeepSeek | opencode | `#max` |
