#! /bin/bash

github_url="git://github.com/harisha/harishaGit.git"
output_dir="/home/harisha/GIT_BACKUP"

repo_name=$(basename ${github_url})
repo_path=${output_dir}/${repo_name} 

echo "Taking backup of GITHUB repo"

if [ -d ${output_dir} ] ; then
    echo "$output_dir does not exist !!!"
    echo "creating output directory"
    mkdir -p ${output_dir}
else
    echo "output directory already exists"
fi

#check if git repository already exists  - yes update
if [ -d $repo_path ] ; then
    prev_path=$PWD
    cd $repo_path
    git pull origin master
    cd $prev_path
#clone
else
    git clone ${github_url} ${output_dir}/$repo_name
fi


