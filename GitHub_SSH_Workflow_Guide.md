# GitHub & SSH Workflow Guide

This document describes the workflow used for creating new projects from
the Raylib template and using GitHub with SSH authentication.

------------------------------------------------------------------------

# Why Use SSH?

-   No GitHub username/password prompts.
-   Secure authentication using an SSH key.
-   `git push` and `git pull` work without repeatedly signing in.

------------------------------------------------------------------------

# One-Time SSH Setup

## 1. Check for an existing SSH key

``` bash
ls -la ~/.ssh
```

## 2. Generate a new SSH key

``` bash
ssh-keygen -t ed25519 -C "your-email@example.com"
```

Press **Enter** to accept the default location.

## 3. Copy the public key

``` bash
cat ~/.ssh/id_ed25519.pub
```

## 4. Add the key to GitHub

1.  GitHub → Settings
2.  SSH and GPG Keys
3.  New SSH Key
4.  Paste the public key
5.  Save

## 5. Test the connection

``` bash
ssh -T git@github.com
```

Type `yes` the first time if prompted.

------------------------------------------------------------------------

# Convert a Repository to SSH

Check the remote:

``` bash
git remote -v
```

Change it:

``` bash
git remote set-url origin git@github.com:<username>/<repository>.git
```

Verify:

``` bash
git remote -v
```

------------------------------------------------------------------------

# Creating a New Project

## Option 1 -- Use the GitHub Template

1.  Click **Use this template**.
2.  Create a new repository.
3.  Clone it:

``` bash
git clone git@github.com:<username>/<repository>.git
```

4.  Open in VS Code.
5.  Change:
    -   `WINDOW_TITLE`
    -   `EXE_NAME`

## Option 2 -- Copy the Template Folder

1.  Copy the Template folder.
2.  Delete `.git`.
3.  Create a GitHub repository.
4.  Run:

``` bash
git init
git remote add origin git@github.com:<username>/<repository>.git
git add .
git commit -m "Initial commit"
git branch -M main
git push -u origin main
```

------------------------------------------------------------------------

# Daily Git Workflow

``` bash
git status
git add .
git commit -m "Describe your changes"
git push
```

------------------------------------------------------------------------

# Useful Commands

``` bash
git branch
git remote -v
git log --oneline
ssh -T git@github.com
```

------------------------------------------------------------------------

# Troubleshooting

## Repository not found

-   Check the repository name.
-   Check the remote URL:

``` bash
git remote -v
```

## Git asks for username/password

Your remote is probably HTTPS.

Switch to SSH:

``` bash
git remote set-url origin git@github.com:<username>/<repository>.git
```

## Empty folders missing

Git does not track empty folders.

Add a `.gitkeep` file.

------------------------------------------------------------------------

# New Project Checklist

-   [ ] Create repository from template
-   [ ] Clone repository
-   [ ] Open in VS Code
-   [ ] Change `WINDOW_TITLE`
-   [ ] Change `EXE_NAME`
-   [ ] Build
-   [ ] Start coding
