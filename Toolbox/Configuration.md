Configurations

# Github
1. Download Git https://git-scm.com/download/win
2. Open cmd check `git --version`
3. Add account in cmd
    ```
    git config --global user.name "<name>"
    git config --global user.email "<email>"
    ```
4. Generate ssh by `ssh-keygen -t rsa -C "<email>"`
5. Copy **id_rsa.pub** content to **github -> settings -> SSH and GPG keys -> SSH keys**
6. Link account in cmd
    ```
    ssh -T git@github.com
    yes
    ```
7. To avoid `RPC failed` while git clone: `git config --global http.version HTTP/1.1`



