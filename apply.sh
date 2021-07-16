# ./train

mkdir -p output

SAMPLES="bosons \
raretop \
ttw \
ttz \
tt1lpowheg \
tt2lpowheg \
tt1l \
tt2l \
vbshww_c2v_4p5"

TREES="variable \
variable_train \
variable_test"

rm -f .jobs.txt
for SAMPLE in ${SAMPLES}; do
    for TREE in ${TREES}; do
        echo "./apply ${SAMPLE} ${TREE}" >> .jobs.txt
    done
done

sh xargs.sh .jobs.txt
