#==============================================================================
#	METHODS COMPARISON
#==============================================================================
# Sebastian Bustamante 		(Universidad de Antioquia), sbustamante@udea.edu.co
# Juan Carlos Muñoz-Cuartas 	(Universidad de Antioquia)

#Commit mesage to update in git repo
MSG = "Last commit"
#Name of tex file
FILE_TEX  = paper
#Latex compiler
LATEX = pdflatex
#Viewer of pdf files
VIEWER = okular
#Latex editor
TEXEDIT = texmaker
#Current date
DATESTAMP=`date +'%Y-%m-%d'`
#Bench
BENCH = bench
#Folder of Codes for Analysis
ACODESFOLD = codes
#Folder of data
DATAFOLD = data


pdflatex:	$(FILE_TEX).tex  
		$(LATEX) $(FILE_TEX).tex 
		#Backup of pdf file (one per day)
		mkdir -p time-machine/${DATESTAMP}
		cp ${FILE_TEX}.pdf time-machine/${DATESTAMP}/${FILE_TEX}.pdf

clean:
		rm -f $(FILE_TEX).aux
		rm -f $(FILE_TEX).out
		rm -f $(FILE_TEX).bbl
		rm -f $(FILE_TEX).log
		make -C bench/codes clean

view: 
		$(VIEWER) $(FILE_TEX).pdf &

edit:
		$(TEXEDIT) $(FILE_TEX).tex &

update:
		git add 			\
		./figures/* 			\
		paper.tex			\
		paper.pdf			\
		makefile			\
		references.bib			\
		README.md			\
		./latex/macros.tex		\

	
compile:
		make -C $(CODESFOLD) compile

help:
		@echo -e 'Makefile Help:'
		@echo -e '\tpdflatex:\t compile the pdf file'
		@echo -e '\tclean:\t\t clean all temporal files'
		@echo -e '\tview:\t\t view the pdf file with standard viewer ($(VIEWER))'
		@echo -e '\tedit:\t\t edit the tex file with standard editor ($(TEXEDIT))'
		@echo -e '\tupdate:\t\t update all files to github repository'
		@echo -e '\tcompile:\t compile the required c codes in $(ACODESFOLD)'
		@echo -e '\thelp:\t\t this help!'