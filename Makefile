# clean:
#	rm -rf /Q[012345678]/code/build/

oneStepGit:
	git add .
	git commit -m "FastGitCommit"
	git push -u origin main
