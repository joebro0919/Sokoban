#include "renderer.h"
#include <osbind.h>
#include <stdio.h>

int main(){

    UINT8 *base = Physbase();

    render_splash(base);

    while(!Cconis()){

    }

    return 0;

}