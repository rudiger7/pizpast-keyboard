---
name: opencode-delegation
description: For the Claude orchestrator only. How to hand a well-scoped code step to a DeepSeek agent through `opencode run`, and how to verify what it did. Use when a plan step is clear, local and low-risk enough that Sonnet would be overkill.
---

# Delegating a step to DeepSeek (opencode)

DeepSeek is the cheap executor. It is not a Claude subagent: run it directly
with Bash, never through a Sonnet/Haiku wrapper. opencode reads `AGENTS.md`
on its own.

## When to delegate

- Good fit: the plan step names its files, the change is local, and "done" is
  checkable (a check in `AGENTS.md` `Checks`, a test, a visible UI change).
- Bad fit: design decisions, cross-area changes, the HID protocol layer, the
  firmware translator (`ol.c`), anything where the plan says "decide" or
  "investigate". Use `executor` or do it yourself.

## Brief

The brief is the plan file, `.claude/plans/<feature>.md`, the same one
`executor` uses. There is no separate prompt file. Make sure the step you hand
over contains: goal, files, constraints, "Done means", and how to verify.

## Run

1. Start from a clean tree (commit or check `git status`); note `git rev-parse HEAD`.
2. Run in the background, log to the scratchpad:

   ```bash
   opencode run --model 'alibaba-token-plan/deepseek-v4.1-flash-1017#max' \
     --title '<feature> step <N>' \
     "Read AGENTS.md, then follow .claude/plans/<feature>.md and do ONLY step <N>. Do not commit. End with: files changed, checks run and their output, anything you could not do." \
     > <scratchpad>/opencode-<feature>-<N>.log 2>&1
   ```

   - `#max` is the reasoning effort; keep it.
   - No `--auto`: the build agent already allows actions, and
     `~/.config/opencode/opencode.json` denies commits, pushes and destructive commands.
   - One run at a time when steps touch the same files.
3. To change instructions mid-run: stop the task, find the `ses_…` id in the
   log, and continue with `opencode run --session <ses_id> "<correction>"`.

## Verify (always — its report can be wrong)

- `git status --porcelain` and `git diff <noted HEAD>`: only the expected files,
  nothing deleted or rewritten outside the step.
- Run every command in `AGENTS.md` `Checks` yourself.
- UI changes: run the app and look at them yourself.
- Check it did nothing in `AGENTS.md` `Never` (PCB files, flashing, writes to a
  connected keyboard, system config).
- Then tick the step in the plan and commit it yourself.
