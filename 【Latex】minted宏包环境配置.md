# 【Latex】minted宏包

## Download
* texlive
* python 2.7
* setuptools
  * `~\Python27\Scripts\pip.exe install *.whl`
  * result：get `easy_install.exe`
* Pygments
  * `~\Python27\Scripts\easy_install.exe Pygments`
  * result：get `pygmentize.exe`

## Build parameter for minted
* 基本编译指令：`*latex -shell-escape filename.tex`
* VS Code 配置：VS Code - settings - latex - settings.json [date: 2020.10.11]
    ```json
    {
        "latex-workshop.latex.recipes": [
            {
                "name": "xelatex",
                "tools": [
                    "xelatex",
                    // "bibtex",
                    // "xelatex",
                    "xelatex",
                    "clean"
                ]
            },
        ],
        "latex-workshop.latex.tools": [
            {
                "name": "xelatex",
                "command": "xelatex",
                "args": [
                    "-shell-escape",            // for minted
                    "-synctex=1",
                    "-interaction=nonstopmode",
                    "-file-line-error",
                    "%DOC%"
                ]
            },

            {
                "name": "bibtex",
                "command": "bibtex",
                "args": [
                    "%DOCFILE%"
                ]
            },

            {
                "name": "clean",
                "command": "clean.bat"
            }
        ]
    }
    ```
* 清理脚本
    ```bat
    ctex -clean
    del *.aux /s
    del *.log /s
    del *.gz /s
    del *.thm /s
    del *.toc /s
    del *.bak /s
    del *.blg /s
    del *.idx /s
    del *.ind /s
    del *.out /s
    del *.bbl /s
    del *.ilg /s
    del *.loe /s
    del *.lof /s
    del *.lot /s
    del *.glo /s
    del *.idx /s
    del *.gls /s
    del *.hd /s
    del *.snm /s
    del *.nav /s
    ```

## Sample
* package
    ```tex
    \usepackage{minted}
    ```
* input from file
    ```tex
    \inputminted[<options>]{<languages>}{<filename>}
    ```
* insert
    ```tex
    \begin{minted}{cpp}
    int main()
    {
        return 0;
    }
    \end{minted}
    ```
* More：https://github.com/gpoore/minted/blob/master/source/minted.pdf