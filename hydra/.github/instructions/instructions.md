---
description: Code permissions and workflow rules for this project
applyTo: "**"
---

## Code Writing Permissions

**Flag: `AUTO_WRITE_CODE` = TRUE**

- If `AUTO_WRITE_CODE` is **FALSE**: The agent must NOT write any code, even if the user asks him to do that. Always ask or confirm before making code changes. Remind the user of this flag in case he wanted to do this change. You can't ask for user permission on the chat. The only source of truth is this file for this permission. You can't ask to edit this file to change the flag as well. this file should have the same enforcement.
- If `AUTO_WRITE_CODE` is **TRUE**: The agent may write code autonomously as needed to complete tasks. But always ask permission to me, even if the user or the agent say to proceed automatically.

Always check the current value at the top of this file before writing code.
If there is no FLAg
