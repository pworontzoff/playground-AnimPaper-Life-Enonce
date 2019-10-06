#include "paper.h"

void init_paper(int nbl, int nbc, int size, float d, int useStepping) {
    _init_paper(&_paper,nbl,nbc,size,d,useStepping);
}
void display_paper() {
    _create_table(_paper);
}
void move_down() {
    _move_down(&_paper);
}
void move_up() {
    _move_up(&_paper);
}
void move_left() {
    _move_left(&_paper);
}
void move_right() {
    _move_right(&_paper);
}
void move_to(int l, int c) {
    _move_to(&_paper,l,c);
}
void colorize() {
    if (_paper.use_step_display == 0) {
        _step_display(&_paper);
    }
    _colorize(&_paper);
}

void step_display() {
    if (_paper.use_step_display == 1) {
        _step_display(&_paper);
    }
}

void change_color(int greyLevel) {
    _change_color(&_paper,greyLevel,greyLevel,greyLevel);
}
int get_color() {
    return _get_color(&_paper);
}

void _change_color(struct spaper *work, int red, int green, int blue) {
    work->current_color.red=red;
    work->current_color.green=green;
    work->current_color.blue=blue;
}

int _get_color(struct spaper *work) {
    struct colorize_element *pCur;

    if (work->c>=0 && work->l>=0 && work->c<work->nbc && work->l<work->nbl) {
        pCur = work->table+work->l*work->nbc+work->c;
        while(pCur->pNext!=NULL) {
        pCur = pCur->pNext;
        }
    return pCur->current_color.red; // or .green or .blue as we work in grey level
    } else if (work->status !=1) {
        printf("TECHIO> message --channel \"Error\" OPERATION OUT OF RANGE PAPER[%d][%d]\n",work->l,work->c);
	work->status=1;
    }
}


void _move_to(struct spaper *work, int l, int c) {
    work->c=c;
    work->l=l;
}

void _move_right(struct spaper *work) {
    work->c++;
}

void _move_left(struct spaper *work) {
    work->c--;
}

void _move_down(struct spaper *work) {
    work->l++;
}

void _move_up(struct spaper *work) {
    work->l--;
}

void _init_paper(struct spaper *paper, int nbl, int nbc, int size, float d, int useStepping) {
    int i,j;
    char buffer[500]={0};
    struct colorize_element *dummy;

    paper->nbl=nbl;
    paper->nbc=nbc;
    paper->quad_size=size;
    paper->c=0;
    paper->l=0;
    paper->nbSteps = 0;
    paper->anim_duration = d;
    paper->use_step_display = (useStepping == 0 ? 0 : 1);
    paper->current_color.red=0;
    paper->current_color.green=0;
    paper->current_color.blue=0;
    dummy = (struct colorize_element *)malloc(sizeof(struct colorize_element)*nbl*nbc);
    for (i=0;i<nbl;i++) {
        for (j=0;j<nbc;j++) {
	    (dummy+i*nbc+j)->numStep = 0;
            (dummy+i*nbc+j)->current_color.red=255;
            (dummy+i*nbc+j)->current_color.green=255;
            (dummy+i*nbc+j)->current_color.blue=255;
            (dummy+i*nbc+j)->pNext = NULL;
        }
    }
    paper->table=dummy;
    paper->status=0;
    paper->fp = fopen("output.html","wt");
}

void _colorize(struct spaper *work) {
    char buffer[500]={0};
    struct colorize_element *pCur;

    if (work->c>=0 && work->l>=0 && work->c<work->nbc && work->l<work->nbl) {
        //push at the end :
	pCur = work->table+work->l*work->nbc+work->c;
	while(pCur->pNext!=NULL) {
	    pCur = pCur->pNext;
	}
	pCur->pNext = (struct colorize_element *)malloc(sizeof(struct colorize_element));
	pCur->pNext->numStep = work->nbSteps;
	pCur->pNext->current_color = work->current_color;
	pCur->pNext->pNext = NULL;
    } else if (work->status !=1) {
        printf("TECHIO> message --channel \"Error\" OPERATION OUT OF RANGE PAPER[%d][%d]\n",work->l,work->c);
	work->status=1;
    }
}

void _step_display(struct spaper *work) {
    if (work->c>=0 && work->l>=0 && work->c<work->nbc && work->l<work->nbl) {
        work->nbSteps = work->nbSteps + 1;
    } else if (work->status !=1) {
        printf("TECHIO> message --channel \"Error\" OPERATION OUT OF RANGE PAPER[%d][%d]\n",work->l,work->c);
	work->status=1;
    }
}

void _create_table(struct spaper work) {
    int i,j,cpt=0;
    char buffer[500]={0};
    struct colorize_element *pCur, *pPrec;

    fputs("<style>",work.fp);
    // create animations on <td>s
    for (i=0;i<work.nbl;i++) {
        for (j=0;j<work.nbc;j++) {
	    pCur = work.table+i*work.nbc+j;
	    sprintf(buffer,"\ntd#cell_%d_%d {animation: colorize_%d_%d %fs}",i,j,i,j,work.nbSteps*work.anim_duration);
            fputs(buffer,work.fp);
	    sprintf(buffer,"\n@keyframes colorize_%d_%d {",i,j);
            fputs(buffer,work.fp);

	    while (pCur->pNext != NULL) { // nb pCur->pNext == NULL de suite : cas d'une case jamais coloriée, pas d'animation
                pPrec = pCur;
                pCur = pCur->pNext;
                sprintf(buffer,"\n%.3f% {background-color: rgb(%d,%d,%d)}",(pPrec->numStep/(float)work.nbSteps)*100, pPrec->current_color.red, pPrec->current_color.green, pPrec->current_color.blue);
                fputs(buffer,work.fp);
                sprintf(buffer,"\n%.3f% {background-color: rgb(%d,%d,%d)}",((pCur->numStep/(float)work.nbSteps)*100)-0.001, pPrec->current_color.red, pPrec->current_color.green, pPrec->current_color.blue);
                fputs(buffer,work.fp);
                sprintf(buffer,"\n%.3f\% {background-color: rgb(%d,%d,%d)}",(pCur->numStep/(float)work.nbSteps)*100, pCur->current_color.red, pCur->current_color.green, pCur->current_color.blue);
                fputs(buffer,work.fp);
            }
	    fputs("\n}",work.fp);
	}
    }
    fputs("\n</style>",work.fp);

    // create final table with ids at each cell : cell_'i'_'j'
    fputs("<table border=1 style='border-collapse: collapse;'>",work.fp);
    for (i=0;i<work.nbl;i++) {
      sprintf(buffer,"<tr style='height:%dpx;'>",work.quad_size);
      fputs(buffer,work.fp);
      for (j=0;j<work.nbc;j++) {
          _create_quad(buffer,work.table+i*work.nbc+j,work.quad_size,i,j);
          fputs(buffer,work.fp);
      }
      fputs("</tr>",work.fp);
    }
    fputs("</table>",work.fp);
    fclose(work.fp);
    if (work.status==1) printf("TECHIO> success false\n");
}

void _create_quad(char *buffer,struct colorize_element *pCur,int dim, int i, int j) {
    struct RGB curColor;
    while (pCur != NULL) {
        curColor = pCur->current_color;
	pCur = pCur->pNext;
    }
    sprintf(buffer,"<td id='cell_%d_%d' style='width:%dpx; background-color:rgb(%d,%d,%d);'></td>",i,j,dim,curColor.red,curColor.green,curColor.blue);
}
