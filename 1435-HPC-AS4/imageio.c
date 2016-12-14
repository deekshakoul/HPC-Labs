

       /*********************************************
       *
       *   file imageio.c
       *
       *   Functions: This file contains
       *     calculate_pad
       *
       *     create_tiff_file_if_needed
       *     c
       *     create_allocate_bmp_file
       *     create_bmp_file_if_needed
       *     create_file_if_needed
       *     create_image_file
       *     create_resized_image_file
       *
       *     does_not_exist
       *     are_not_same_size
       *
       *     extract_long_from_buffer
       *     extract_short_from_buffer
       *     extract_ulong_from_buffer
       *     extract_ushort_from_buffer
       *
       *     equate_tiff_headers
       *     equate_bmpfileheaders
       *     equate_bitmapheaders
       *
       *     insert_short_into_buffer
       *     insert_ushort_into_buffer
       *     insert_long_into_buffer
       *     insert_ulong_into_buffer
       *
       *     allocate_image_array
       *     free_image_array
       *     flip_image_array
       *
       *     get_image_size
       *     get_bitsperpixel
       *     get_lsb
       *
       *     is_a_bmp
       *     is_a_tiff
       *
       *     print_bmp_file_header
       *     print_bm_file_header
       *     print_color_table
       *
       *     read_tiff_header
       *     read_tiff_image
       *     read_line
       *     read_bmp_file_header
       *     read_bm_header
       *     read_color_table
       *     read_bmp_image
       *     read_image_array
       *
       *     round_off_image_size
       *
       *     seek_to_first_line
       *     seek_to_end_of_line
       *
       *     write_array_into_tiff_file
       *     write_tiff_image
       *     write_bmp_image
       *     write_image_array
       *     write_line
       *
       *   Purpose:
       *     This file contains the subroutines that 
       *     read and write tiff and bmp image files.
       *
       *   External Calls:
       *      none
       *
       *   Modifications:
       *      23 June 1990 - created
       *      28 March 1993 - using fopen, fread, fseek
       *          instead of my_open, my_read, lseek.
       *      25 June 1990 - created
       *      27 March 1993 - use fopen, fread, fseek
       *           instead of the earlier open, read,
       *           seek, etc.
       *      21 April 1998 - modified to work with
       *           an entire image at one time.
       *      18 September 1998 - imagio.c was created
       *           by combining tiff.c brwtiff.c and
       *           functions written for bmp file io.
       *
       ************************************************/





#include "cips.h"
#include <math.h>
#include "omp.h"

   /****************************************
   *
   *   extract_long_from_buffer(...
   *
   *   This takes a four byte long out of a
   *   buffer of characters.
   *
   *   It is important to know the byte order
   *   LSB or MSB.
   *
   ****************************************/

extract_long_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int       lsb, start;
   long  *number;
{
   int i;
   union long_char_union lcu;

   if(lsb == 1){
      lcu.l_alpha[0] = buffer[start+0];
      lcu.l_alpha[1] = buffer[start+1];
      lcu.l_alpha[2] = buffer[start+2];
      lcu.l_alpha[3] = buffer[start+3];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.l_alpha[0] = buffer[start+3];
      lcu.l_alpha[1] = buffer[start+2];
      lcu.l_alpha[2] = buffer[start+1];
      lcu.l_alpha[3] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.l_num;


}  /* ends extract_long_from_buffer */






   /****************************************
   *
   *   extract_ulong_from_buffer(...
   *
   *   This takes a four byte unsigned long 
   *   out of a buffer of characters.
   *
   *   It is important to know the byte order
   *   LSB or MSB.
   *
   ****************************************/

extract_ulong_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int       lsb, start;
   unsigned long  *number;
{
   int i;
   union ulong_char_union lcu;

   if(lsb == 1){
      lcu.l_alpha[0] = buffer[start+0];
      lcu.l_alpha[1] = buffer[start+1];
      lcu.l_alpha[2] = buffer[start+2];
      lcu.l_alpha[3] = buffer[start+3];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.l_alpha[0] = buffer[start+3];
      lcu.l_alpha[1] = buffer[start+2];
      lcu.l_alpha[2] = buffer[start+1];
      lcu.l_alpha[3] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.l_num;
}  /* ends extract_ulong_from_buffer */




   /****************************************
   *
   *   extract_short_from_buffer(...
   *
   *   This takes a two byte short out of a
   *   buffer of characters.
   *
   *   It is important to know the byte order
   *   LSB or MSB.
   *
   ****************************************/

extract_short_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int       lsb, start;
   short *number;
{

   int i;
   union short_char_union lcu;

   if(lsb == 1){
      lcu.s_alpha[0] = buffer[start+0];
      lcu.s_alpha[1] = buffer[start+1];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.s_alpha[0] = buffer[start+1];
      lcu.s_alpha[1] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.s_num;


}  /* ends extract_short_from_buffer */



 


   /****************************************
   *
   *   extract_ushort_from_buffer(...
   *
   *   This takes a two byte unsiged short 
   *   out of a buffer of characters.
   *
   *   It is important to know the byte order
   *   LSB or MSB.
   *
   ****************************************/

extract_ushort_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int       lsb, start;
   unsigned short *number;
{

   int i;
   union ushort_char_union lcu;

   if(lsb == 1){
      lcu.s_alpha[0] = buffer[start+0];
      lcu.s_alpha[1] = buffer[start+1];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.s_alpha[0] = buffer[start+1];
      lcu.s_alpha[1] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.s_num;
}  /* ends extract_ushort_from_buffer */





   /****************************************
   *
   *   allocate_image_array(...
   *
   *   This function allocates memory for
   *   a two-dimensional image array.
   *
   ****************************************/

short **allocate_image_array(length, width)
   long  length, width;
{
   int i;
   short **the_array;

   the_array = malloc(length * sizeof(short  *));
   for(i=0; i<length; i++){
      the_array[i] = malloc(width * sizeof(short ));
      if(the_array[i] == '\0'){
         printf("\n\tmalloc of the_image[%d] failed", i);
      }  /* ends if */
   }  /* ends loop over i */
   return(the_array);

}  /* ends allocate_image_array */






   /****************************************
   *
   *   free_image_array(...
   *
   *   This function frees up the memory 
   *   used by a two-dimensional imaage array.
   *
   ****************************************/

int free_image_array(the_array, length)
   short **the_array;
   long  length;
{
   int i;
   for(i=0; i<length; i++)
      free(the_array[i]);
   return(1);
}  /* ends free_image_array */




 











   /***************************************
   *
   *   insert_short_into_buffer(...
   *
   *   This inserts a two byte short into a
   *   buffer of characters.  It does this
   *   is LSB order.
   *
   ***************************************/


insert_short_into_buffer(buffer, start, number)
    char  buffer[];
    int   start;
    short number;
{
    union short_char_union lsu;

    lsu.s_num       = number;
    buffer[start+0] = lsu.s_alpha[0];
    buffer[start+1] = lsu.s_alpha[1];

}  /* ends insert_short_into_buffer */






   /***************************************
   *
   *   insert_ushort_into_buffer(...
   *
   *   This inserts a two byte unsigned 
   *   short into a buffer of characters.  
   *   It does this is LSB order.
   *
   ***************************************/

insert_ushort_into_buffer(buffer, start, number)
    char  buffer[];
    int   start;
    unsigned short number;
{
    union ushort_char_union lsu;

    lsu.s_num       = number;
    buffer[start+0] = lsu.s_alpha[0];
    buffer[start+1] = lsu.s_alpha[1];

}  /* ends insert_short_into_buffer */




   /***************************************
   *
   *   insert_long_into_buffer(...
   *
   *   This inserts a four byte long into a
   *   buffer of characters.  It does this
   *   is LSB order.
   *
   ***************************************/



insert_long_into_buffer(buffer, start, number)
    char buffer[];
    int  start;
    long number;
{
    union long_char_union lsu;

    lsu.l_num       = number;
    buffer[start+0] = lsu.l_alpha[0];
    buffer[start+1] = lsu.l_alpha[1];
    buffer[start+2] = lsu.l_alpha[2];
    buffer[start+3] = lsu.l_alpha[3];

}  /* ends insert_short_into_buffer */





   /***************************************
   *
   *   insert_ulong_into_buffer(...
   *
   *   This inserts a four byte unsigned 
   *   long into a buffer of characters.  
   *   It does this is LSB order.
   *
   ***************************************/

insert_ulong_into_buffer(buffer, start, number)
    char buffer[];
    int  start;
    unsigned long number;
{
    union ulong_char_union lsu;

    lsu.l_num       = number;
    buffer[start+0] = lsu.l_alpha[0];
    buffer[start+1] = lsu.l_alpha[1];
    buffer[start+2] = lsu.l_alpha[2];
    buffer[start+3] = lsu.l_alpha[3];

}  /* ends insert_ulong_into_buffer */




   /***************************************
   *
   *   round_off_image_size(...
   *
   *   This takes the image header and rounds
   *   it off to a multiple of ROWS and COLS.
   *   e.g. if width=123 it returns 1.
   *
   ***************************************/


round_off_image_size(image_header, length, width)
    int    *length, *width;
    struct tiff_header_struct *image_header;
{
   *length = (ROWS-10 + image_header->image_length)/ROWS;
   *width  = (COLS-10 + image_header->image_width)/COLS;
} /* ends round_off_image_size */





    /***********************************************
    *
    *    does_not_exist(...
    *
    *    This function checks the disk to see if
    *    a file exists.  If the file is there this
    *    function returns a 0, if it does not exist
    *    this function returns a 1.
    *
    ***********************************************/

does_not_exist(file_name)
    char file_name[];
{
   FILE *image_file;
   int  result;

   result = 1;
   image_file = fopen(file_name, "rb");
   if(image_file != NULL){
      result = 0;
      fclose(image_file);
   }
   return(result);
}  /* ends does_not_exist */










      /******************************************
      *
      *   read_bmp_file_header(...
      *
      *   This function reads the bmpfileheader
      *   structure from the top of a bmp
      *   image file.
      *
      ******************************************/

read_bmp_file_header(file_name,
                     file_header)
   char *file_name;
   struct bmpfileheader *file_header;
{
   char  buffer[10];
   long  ll;
   short ss;
   unsigned long  ull;
   unsigned short uss;
   FILE     *fp;

   fp = fopen(file_name, "rb");

   fread(buffer, 1, 2, fp);
   extract_ushort_from_buffer(buffer, 1, 0, &uss);
   file_header->filetype = uss;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   file_header->filesize = ull;

   fread(buffer, 1, 2, fp);
   extract_short_from_buffer(buffer, 1, 0, &ss);
   file_header->reserved1 = ss;

   fread(buffer, 1, 2, fp);
   extract_short_from_buffer(buffer, 1, 0, &ss);
   file_header->reserved2 = ss;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   file_header->bitmapoffset = ull;

   fclose(fp);

}  /* ends read_bmp_file_header */



      /******************************************
      *
      *   print_bmp_file_header(...
      *
      *   This function printfs parts of the
      *   bmpfileheader structure.
      *
      ******************************************/

print_bmp_file_header(struct bmpfileheader *file_header)
{
 printf("\nfile type %x", file_header->filetype);
 printf("\nfile size %d", file_header->filesize);
 printf("\nbit map offset %d", file_header->bitmapoffset);
}




      /******************************************
      *
      *   read_bm_header(...
      *
      *   This function reads the bitmapheader
      *   structure from the top of a bmp
      *   image file.
      *
      ******************************************/

read_bm_header(file_name,
               bmheader)
   char *file_name;
   struct bitmapheader *bmheader;
{
   char  buffer[10];
   long  ll;
   short ss;
   unsigned long  ull;
   unsigned short uss;
   FILE *fp;

   fp = fopen(file_name, "rb");

      /****************************************
      *
      *   Seek past the first 14 byte header.
      *
      ****************************************/

   fseek(fp, 14, SEEK_SET);

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->size = ull;

   fread(buffer, 1, 4, fp);
   extract_long_from_buffer(buffer, 1, 0, &ll);
   bmheader->width = ll;

   fread(buffer, 1, 4, fp);
   extract_long_from_buffer(buffer, 1, 0, &ll);
   bmheader->height = ll;

   fread(buffer, 1, 2, fp);
   extract_ushort_from_buffer(buffer, 1, 0, &uss);
   bmheader->planes = uss;

   fread(buffer, 1, 2, fp);
   extract_ushort_from_buffer(buffer, 1, 0, &uss);
   bmheader->bitsperpixel = uss;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->compression = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->sizeofbitmap = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->horzres = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->vertres = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->colorsused = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->colorsimp = ull;

   fclose(fp);

}  /* ends read_bm_header */



      /******************************************
      *
      *   print_bm_header(...
      *
      *   This function printfs parts of the
      *   bitmapheader structure.
      *
      ******************************************/

print_bm_header(bmheader)
   struct bitmapheader *bmheader;
{
 printf("\nwidth %d", bmheader->width);
 printf("\nheight %d", bmheader->height);
 printf("\nplanes %d", bmheader->planes);
 printf("\nbitsperpixel %d", bmheader->bitsperpixel);
 printf("\ncolorsused %d", bmheader->colorsused);
 printf("\ncolorsimp %d", bmheader->colorsimp);
}




      /******************************************
      *
      *   read_color_table(...
      *
      *   This function reads the color table
      *   from a bmp image file.
      *
      ******************************************/

read_color_table(file_name, rgb, size)
   char   *file_name;
   struct ctstruct *rgb;
   int    size;
{
   int  i;
   char buffer[10];
   FILE *fp;

   fp = fopen(file_name, "rb");

   fseek(fp, 54, SEEK_SET);

   for(i=0; i<size; i++){
      fread(buffer, 1, 1, fp);
      rgb[i].blue = buffer[0];
      fread(buffer, 1, 1, fp);
      rgb[i].green = buffer[0];
      fread(buffer, 1, 1, fp);
      rgb[i].red = buffer[0];
      fread(buffer, 1, 1, fp);
         /* fourth byte nothing */
   }  /* ends loop over i */

   fclose(fp);

}  /* ends read_color_table */




      /******************************************
      *
      *   print_color_table(...
      *
      *   This function printfs the color table
      *   from a bmp file.
      *
      ******************************************/

print_color_table(struct ctstruct *rgb, int size)
{
   int i;

   for(i=0; i<size; i++){
      printf("\n %d %d %d",
      rgb[i].blue,rgb[i].green,rgb[i].red);
   }  /* ends loop over i */
}  /* ends print_color_table */






      /******************************************
      *
      *   flip_image_array(...
      *
      *   This function flips an image array
      *   about its horizontal mid-point.
      *
      ******************************************/

flip_image_array(the_image, rows, cols)
   long   cols, rows;
   short  **the_image;
{
   int  i, j;
   long rd2;
   short **temp;

   temp = allocate_image_array(rows, cols);
   rd2  = rows/2;
   for(i=0; i<rd2; i++){
      for(j=0; j<cols; j++){
         temp[rows-1-i][j] = the_image[i][j];
      }  /* ends loop over j */
   }  /* ends loop over i */

   for(i=rd2; i<rows; i++){
      for(j=0; j<cols; j++){
         temp[rows-1-i][j] = the_image[i][j];
      }  /* ends loop over j */
   }  /* ends loop over i */

   for(i=0; i<rows; i++)
      for(j=0; j<cols; j++)
         the_image[i][j] = temp[i][j];

   free_image_array(temp, rows);
}  /* ends flip_image_array */







      /******************************************
      *
      *   read_bmp_image(...
      *
      *   This function reads the image array
      *   from a bmp file.  
      *
      *   It only works for 8-bit images.
      *
      ******************************************/

short **read_bmp_image(file_name, lengthptr, breadthptr)
   char  *file_name;
	long *lengthptr, *breadthptr;
{
   FILE   *fp;
   int    i, j;
   int    negative = 0,
          pad      = 0,
          place    = 0;
   long   colors   = 0,
          height   = 0,
          position = 0,
          width    = 0;
   struct bmpfileheader file_header;
   struct bitmapheader  bmheader;
   struct ctstruct rgb[GRAY_LEVELS+1];
   unsigned char uc;

   read_bmp_file_header(file_name, &file_header);
   read_bm_header(file_name, &bmheader);
   /*if(bmheader.bitsperpixel != 8){
      printf("\nCannot read image when bits per"
      "pixel is not 8");
      exit(1);
   }*/

   if(bmheader.colorsused == 0)
      colors = GRAY_LEVELS + 1;
   else
      colors = bmheader.colorsused;
   read_color_table(file_name, &rgb, colors);

   fp = fopen(file_name, "rb");
   fseek(fp, file_header.bitmapoffset, SEEK_SET);

   width = bmheader.width;
   if(bmheader.height < 0){
      height   = bmheader.height * (-1);
      negative = 1;
   }
   else
      height = bmheader.height;

   pad = calculate_pad(width);
	
printf("I'm running height = %d, width = %d\n", height, width);

	short **array = allocate_image_array(height, width);  ///alllocate array
	//short **array1 = allocate_image_array(height, width); 
 for(i=0; i<height; i++){
      for(j=0; j<width; j++){
         place = fgetc(fp);
         uc = (place & 0xff);
         place = uc;
         array[i][j] = rgb[place].blue;
      }  /* ends loop over j */
      if(pad != 0){
         position = fseek(fp, pad, SEEK_CUR);
      }  /* ends if pad 1= 0 */
   }  /* ends loop over i */

   if(negative == 0)
      flip_image_array(array, height, width);
	*lengthptr = height;
	*breadthptr = width;
//int i , j;
	/*for(i = 0; i < 256; i++){
		for(j = 0; j < 256; j++){
			array[i][j] = 0;
		}
		printf("\n");
	}*/
	printf("Done loading image in the array\n");
	return array;


}  /* ends read_bmp_image */






   /*********************************************
   *
   *   create_allocate_bmp_file(...
   *
   *   The calling routine must set the 
   *   height and width.  This routine will set
   *   everything else.
   *
   **********************************************/

create_allocate_bmp_file(file_name,
                         file_header,
                         bmheader)
   char  *file_name;
   struct bmpfileheader *file_header;
   struct bitmapheader  *bmheader;
{
   char buffer[100];
   int  i, pad = 0;
   FILE *fp;

   pad = calculate_pad(bmheader->width);

   bmheader->size         =  40;
   bmheader->planes       =   1;
   bmheader->bitsperpixel =   8;
   bmheader->compression  =   0;
   bmheader->sizeofbitmap = bmheader->height * 
                            (bmheader->width + pad);
   bmheader->horzres      = 300;
   bmheader->vertres      = 300;
   bmheader->colorsused   = 256;
   bmheader->colorsimp    = 256;

   file_header->filetype     = 0x4D42;
   file_header->reserved1    =  0;
   file_header->reserved2    =  0;
   file_header->bitmapoffset = 14 + 
                               bmheader->size +
                               bmheader->colorsused*4;
   file_header->filesize     = file_header->bitmapoffset +
                               bmheader->sizeofbitmap;

   if((fp = fopen(file_name, "wb")) == NULL){
      printf("\nERROR Could not create file %s",
             file_name);
      exit(2);
   }

      /*********************************************
      *
      *   Write the 14-byte bmp file header.
      *
      *********************************************/

   insert_ushort_into_buffer(buffer, 0, file_header->filetype);
   fwrite(buffer, 1, 2, fp);

   insert_ulong_into_buffer(buffer, 0, file_header->filesize);
   fwrite(buffer, 1, 4, fp);

   insert_short_into_buffer(buffer, 0, file_header->reserved1);
   fwrite(buffer, 1, 2, fp);

   insert_short_into_buffer(buffer, 0, file_header->reserved2);
   fwrite(buffer, 1, 2, fp);

   insert_ulong_into_buffer(buffer, 0, file_header->bitmapoffset);
   fwrite(buffer, 1, 4, fp);


      /*********************************************
      *
      *   Write the 40-byte bit map header.
      *
      *********************************************/

   insert_ulong_into_buffer(buffer, 0, bmheader->size);
   fwrite(buffer, 1, 4, fp);

   insert_long_into_buffer(buffer, 0, bmheader->width);
   fwrite(buffer, 1, 4, fp);

   insert_long_into_buffer(buffer, 0, bmheader->height);
   fwrite(buffer, 1, 4, fp);

   insert_ushort_into_buffer(buffer, 0, bmheader->planes);
   fwrite(buffer, 1, 2, fp);

   insert_ushort_into_buffer(buffer, 0, bmheader->bitsperpixel);
   fwrite(buffer, 1, 2, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->compression);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->sizeofbitmap);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->horzres);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->vertres);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->colorsused);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->colorsimp);
   fwrite(buffer, 1, 4, fp);

      /*********************************************
      *
      *   Write a blank color table.
      *   It has 256 entries (number of colors)
      *   that are each 4 bytes.
      *
      *********************************************/

   buffer[0] = 0x00;

   for(i=0; i<(256*4); i++)
      fwrite(buffer, 1, 1, fp);

      /*********************************************
      *
      *   Write a zero image.  
      *
      *********************************************/

   buffer[0] = 0x00;

   for(i=0; i<bmheader->sizeofbitmap; i++)
      fwrite(buffer, 1, 1, fp);

   fclose(fp);

}  /* ends create_allocate_bmp_file */







      /******************************************
      *
      *   create_bmp_file_if_needed(...
      *
      *   This function allocates a bmp image
      *   file it it does not exist.  It uses
      *   the header information from the input
      *   image name.
      *
      ******************************************/

create_bmp_file_if_needed(in_name, out_name, out_image)
   char in_name[], out_name[];
   short **out_image;
{
   int    length, width;
   struct bmpfileheader file_header;
   struct bitmapheader  bmheader;

   if(does_not_exist(out_name)){
      printf("\n\n output file does not exist %s",
               out_name);
      read_bm_header(in_name, &bmheader);
      create_allocate_bmp_file(out_name, &file_header, &bmheader);
      printf("\nBFIN> Created %s", out_name);
   }  /* ends if does_not_exist */
}  /* ends bmp_file_if_needed */





      /******************************************
      *
      *   write_bmp_image(...
      *
      *   This function writes an image array
      *   to a bmp image file.
      *
      ******************************************/

write_bmp_image(file_name, array)
   char   *file_name;
   short  **array;
{
   char   *buffer, c;
   FILE   *image_file;
   int    pad = 0,
          position;
   int    bytes, i, j;
   long   height = 0, width = 0;
   struct bitmapheader  bmheader;
   struct bmpfileheader file_header;
   struct ctstruct rgb[GRAY_LEVELS+1];
   union  short_char_union scu;

   read_bmp_file_header(file_name, &file_header);
   read_bm_header(file_name, &bmheader);

   height = bmheader.height;
   width  = bmheader.width;
   if(height < 0) height = height*(-1);

   buffer = (char  *) malloc(width * sizeof(char ));
   for(i=0; i<width; i++)
      buffer[i] = '\0';

   image_file = fopen(file_name, "rb+");

      /****************************************
      *
      *   Write the color table first.
      *
      ****************************************/

   position   = fseek(image_file, 54, SEEK_SET);
   for(i=0; i<GRAY_LEVELS+1; i++){
      rgb[i].blue  = i;
      rgb[i].green = i;
      rgb[i].red   = i;
   }  /* ends loop over i */

   for(i=0; i<bmheader.colorsused; i++){
      buffer[0] = rgb[i].blue;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = rgb[i].green;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = rgb[i].red;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = 0x00;
      fwrite(buffer , 1, 1, image_file);
   }  /* ends loop over i */

   position   = fseek(image_file,
                      file_header.bitmapoffset, 
                      SEEK_SET);

   pad = calculate_pad(width);

   for(i=0; i<height; i++){
      for(j=0; j<width; j++){

         if(bmheader.bitsperpixel == 8){
            scu.s_num = 0;
            if(bmheader.height > 0)
               scu.s_num = array[height-1-i][j];
            else
               scu.s_num = array[i][j];
            buffer[j] = scu.s_alpha[0];
         }  /* ends if bits_per_pixel == 8 */
         else{
            printf("\nERROR bitsperpixel is not 8");
            exit(1);
         }
      }  /* ends loop over j */

      bytes = fwrite(buffer, 1, width, image_file);

      if(pad != 0){
         for(j=0; j<pad; j++)
            buffer[j] = 0x00;
         fwrite(buffer, 1, pad, image_file);
      }  /* ends if pad != 0 */

   }  /* ends loop over i */

   fclose(image_file);
   free(buffer);
}  /* ends write_bmp_image */





      /******************************************
      *
      *   calculate_pad(...
      *
      *   This function calculates the pad needed
      *   at the end of each row of pixels in a
      *   bmp image.
      *
      ******************************************/

int calculate_pad(width)
   long width;
{
   int pad = 0;
   pad = ( (width%4) == 0) ? 0 : (4-(width%4));
   return(pad);
}  /* ends calculate_pad */



   /**********************************************
   *
   *   get_image_size(...
   *
   *   This function reads the rows and cols
   *   from the header of either a tiff or bmp
   *   image file.
   *
   *   IF IT CANNOT FIND THIS INFORMATION,
   *   it returns a ZERO.
   *
   ***********************************************/

int get_image_size(file_name, rows, cols)
   char *file_name;
   long *cols, *rows;
{
   int is_bmp  = 0,
       result  = 0;
   struct bitmapheader bmph;
 
   if(is_a_bmp(file_name)){
      is_bmp = 1;
      read_bm_header(file_name, &bmph);
      *rows = bmph.height;
      *cols = bmph.width;
   }  /* ends if is_a_bmp */

   if(is_bmp == 1)
      result = 1;

   return(result);
}  /* ends get_image_size */






      /******************************************
      *
      *   get_bitsperpixel(...
      *
      *   This function reads the bits per pixel
      *   from either a tiff or bmp image file.
      *
      ******************************************/

int get_bitsperpixel(file_name, bitsperpixel)
   char *file_name;
   long *bitsperpixel;
{
   int    is_bmp  = 0,
          result  = 0;
   long   temp;
   struct bitmapheader bmph;

   if(is_a_bmp(file_name)){
      is_bmp = 1;
      read_bm_header(file_name, &bmph);
      temp = (long)bmph.bitsperpixel;
      *bitsperpixel = temp;
   }  /* ends if is_a_bmp */

   
   if(is_bmp == 1)
      result = 1;

   return(result);
}  /* ends get_image_size */






      /******************************************
      *
      *   get_lsb(...
      *
      *   This function reads the lsb flag
      *   from a tiff image file.
      *
      ******************************************/

int get_lsb(name)
   char *name;
{
   int   result = 0;
   struct tiff_header_struct tiff_header;

   if(is_a_bmp(name))
      result = 1;

   return(result);

}  /*  ends get_lsb */








   /**********************************************
   *
   *   is_a_bmp(...
   *
   *   This function looks at a file to see if it
   *   is a bmp file.  First look at the file
   *   extension.  Next look at the filetype to
   *   ensure it is 0x4d42.
   *
   ***********************************************/

int is_a_bmp(file_name)
   char *file_name;
{
   char   *cc;
   int    result = 0;
   struct bmpfileheader file_header;

   cc = strstr(file_name, ".bmp");
   if(cc == NULL)
      return(result);

   read_bmp_file_header(file_name, &file_header);
	print_bmp_file_header(&file_header);
   if(file_header.filetype != 0x4d42)
      return(result);

   result = 1;
   return(result);
}  /* ends is_a_bmp */







   /*******************************************
   *
   *   read_image_array(...
   *
   *   This routine reads the image data from
   *   either a tiff or bmp image.
   *
   ********************************************/

read_image_array(file_name, array)
   char  *file_name;
   short **array;
{
   int ok = 0;
   
   if(is_a_bmp(file_name)){
      read_bmp_image(file_name, array);
      ok = 1;
   }

   if(ok == 0){
      printf("\nERROR could not read file %s",
             file_name);
      exit(1);
   }

}  /* ends read_image_array */







   /*******************************************
   *
   *   write_image_array(...
   *
   *   This routine writes the image data to
   *   either a tiff or bmp image.
   *
   ********************************************/

write_image_array(file_name, array)
   char  *file_name;
   short **array;
{
   int ok = 0;

   if(is_a_bmp(file_name)){
      write_bmp_image(file_name, array);
      ok = 1;
   }

   if(ok == 0){
      printf("\nERROR could not write file %s",
             file_name);
      exit(1);
   }

}  /* ends write_image_array */





   /*********************************************
   *
   *   equate_bmpfileheaders(...
   *
   *   This function sets the elements of the
   *   destination header to the values of the
   *   source header.
   *
   *********************************************/

equate_bmpfileheaders(src, dest)
   struct bmpfileheader *src, *dest;
{
   dest->filetype     = src->filetype;
   dest->filesize     = src->filesize;
   dest->reserved1    = src->reserved1;
   dest->reserved2    = src->reserved2;
   dest->bitmapoffset = src->bitmapoffset;
}  /* ends equate_bmpfileheaders */



   /*********************************************
   *
   *   equate_bitmapheaders(...
   *
   *   This function sets the elements of the
   *   destination header to the values of the
   *   source header.
   *
   *********************************************/

equate_bitmapheaders(src, dest)
   struct bitmapheader *src, *dest;
{
   dest->size         = src->size;
   dest->width        = src->width;
   dest->height       = src->width;
   dest->planes       = src->planes;
   dest->bitsperpixel = src->bitsperpixel;
   dest->compression  = src->compression;
   dest->sizeofbitmap = src->sizeofbitmap;
   dest->horzres      = src->horzres;
   dest->vertres      = src->vertres;
   dest->colorsused   = src->colorsused;
   dest->colorsimp    = src->colorsimp;
}  /* ends equate_bitmapheader */






   /*********************************************
   *
   *   are_not_same_size(...
   *
   *   This function checks the rows and cols
   *   of two images whose names are passed.
   *   It returns a 1 if the images are not
   *   the same size.
   *
   *********************************************/

int are_not_same_size(file1, file2)
   char *file1, *file2;
{
   int  result = 0;
   long cols1  = 1, 
        cols2  = 2, 
        rows1  = 3, 
        rows2  = 4;

   get_image_size(file1, &rows1, &cols1);
   get_image_size(file2, &rows2, &cols2);

   if(rows1 != rows2  ||  cols1 != cols2)
      result = 1;

   return(result);

}  /* ends are_not_same_size */






   /*********************************************
   *
   *   create_file_if_needed(...
   *
   *   This function creates an output file
   *   if it does not exist.  It can create
   *   the output file as a tiff or a bmp
   *   based on the input file type.
   *
   *********************************************/

create_file_if_needed(in_name, out_name, array)
   char *in_name, *out_name;
   short **array;
{
  
   if(is_a_bmp(in_name)){
      create_bmp_file_if_needed(in_name, 
                                out_name, 
                                array);
   }

}  /* ends create_file_if_needed */







   /*********************************************
   *
   *   create_image_file(...
   *
   *   This function creates an output image file.
   *   It uses the input image file as a pattern.
   *
   *********************************************/

create_image_file(in_name, out_name)
   char *in_name, *out_name;
{
   struct bmpfileheader      bmp_file_header;
   struct bitmapheader       bmheader;
   struct tiff_header_struct tiff_file_header;

   if(is_a_bmp(in_name)){
      read_bmp_file_header(in_name, 
                           &bmp_file_header);
      read_bm_header(in_name, &bmheader);
      create_allocate_bmp_file(out_name, 
                               &bmp_file_header, 
                               &bmheader);
   }

}  /* ends create_image_file */








   /*********************************************
   *
   *   create_resized_image_file(...
   *
   *   This function creates an output image file.
   *   It uses the input image file as a pattern.
   *
   *********************************************/

create_resized_image_file(in_name, out_name,
                          length, width)
   char *in_name, *out_name;
   long length, width;
{
   struct bmpfileheader      bmp_file_header;
   struct bitmapheader       bmheader;
  
   if(is_a_bmp(in_name)){
      read_bmp_file_header(in_name, 
                           &bmp_file_header);
      read_bm_header(in_name, &bmheader);
      bmheader.height = length;
      bmheader.width  = width;
      create_allocate_bmp_file(out_name, 
                               &bmp_file_header, 
                               &bmheader);
   }

}  /* ends create_resided_image_file */

short **warp_image_parallel(in_array, height, width, threads)
	short **in_array;
	long height, width;
	int threads;
{
	long xp, yp, tx = width/2, ty = height/2;
	float x, y, radius, theta, PI = 3.141527f, DRAD = 180.0f / PI;
	short **out_array = allocate_image_array(height, width);
	//printf("%d\n", threads);
	double time = omp_get_wtime();
#pragma omp parallel for num_threads(threads)\
shared(in_array, out_array, width, height) \
private(x, y, radius, theta, xp, yp)
	for (yp = 0; yp < height; yp++) {
		for (xp = 0; xp < width; xp++) {
			radius = sqrtf((xp - tx) * (xp - tx) + (yp - ty) * (yp - ty));
			theta = (radius / 2) * DRAD;
			x = cos(theta) * (xp - tx) - sin(theta) * (yp - ty) + tx;
			y = sin(theta) * (xp - tx) + cos(theta) * (yp - ty) + ty;
			//scale(array, out_array,width, height);

			out_array[xp][yp] = bilinear_interpolate(in_array, x, y, height, width);
		}
	}
	
printf("Time taken for warping under PARALLEL %d x %d image using %d threads is : %lf\n", height, width, threads, omp_get_wtime() - time);
		return out_array;
}
short **warp_image_serial(in_array, height, width, threads)
	short **in_array;
	long height, width;
	int threads;
{
	long xp, yp, tx = width/2, ty = height/2;
	float x, y, radius, theta, PI = 3.141527f, DRAD = 180.0f / PI;
	short **out_array = allocate_image_array(height, width);
	double time = omp_get_wtime();
	for (yp = 0; yp < height; yp++) {
		for (xp = 0; xp < width; xp++) {
			radius = sqrtf((xp - tx) * (xp - tx) + (yp - ty) * (yp - ty));
			theta = (1/(radius / 2)) * DRAD;
			x = cos(theta) * (xp - tx) - sin(theta) * (yp - ty) + tx;
			y = sin(theta) * (xp - tx) + cos(theta) * (yp - ty) + ty;
			//scale(array, out_array,width, height);

			out_array[xp][yp] = bilinear_interpolate(in_array, x, y, height, width);
		}
	}
	
	printf("Time taken for warping under SERIAL CODE %d x %d image is : %lf\n", height, width, omp_get_wtime() - time);
		return out_array;
}


