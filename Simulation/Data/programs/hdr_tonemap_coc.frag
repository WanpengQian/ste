 ފ         #     �                GLSL.std.450              	       main    n  �  �  �               �   
 GL_GOOGLE_cpp_style_line_directive       main         RGBtoXYZ(vf3;     
   rgb      XYZtoxyY(vf3;        XYZ      XYZtoRGB(vf3;        xyz      xyYtoXYZ(vf3;        xyY      uint_to_sfloat_order_preserving(u1;      f        red_response(f1;         scotopic      "   monochromaticity(f1;      !   scotopic      (   hdr_bin(f1;f1;f1;     %   max_lum   &   min_lum   '   l     +   hdr_lum(f1;   *   l    	 1   hdr_lum_to_luminance(vf2;     0   l     4   tonemap(f1;   3   l    	 7   hdr_lum_from_hdr_params(u1;   6   param     >   hdr_bloom(vf3;f1;f1;      ;   rgb   <   luminance     =   mesopic   A   hdr_tonemap(f1;   @   luminance    
 E   conversion_matrix_rgb_to_xyz     
 S   conversion_matrix_xyz_to_rgb      f   XYZtotal      �   Y_y   �   XYZ   �   mask      �   range     �   bin_size      �   param     �   x     �   T     �   histogram_sums    �       histogram     �         �   l     �   param       min_lum     hdr_bokeh_parameters            lum_min        lum_max        focus    	   hdr_bokeh_parameters_buffer         params              param     
  max_lum     param       fbin        param       param       param       bin   "  param     %  toned_bin_start   1  toned_bin_end     5  bin_range     >  bin_hdr_lum_range     L  bin_luminance_range   M  param     P  frac      [  toned_l   b  param     g  xyY   k  hdr   n  gl_FragCoord      v  x     y  vision_properties_coord     vision_properties    
 �  hdr_vision_properties_texture     �  scotopic      �  mesopic   �  red_coef      �  param     �  monochrm      �  param     �  rgb   �  param     �  param     �  param     �  param     �  tonemapped_luminance      �  param     �  param     �  param     �  rgb_lum   �  bloom     �  param     �  param     �  param     �  rgbout    �  bloomout      �  uv  G  �         H  �          H  �          H  �       #       G  �      G  �   "       G  �   !      H        #       H       #      H       #      H           H           H        #       G       G    "       G    !      G  k  "       G  k  !       G  n        G  �  "       G  �  !      G  �         G  �        G  �              !                                        !  	                                  !                       !           !  $                 -            .      -   !  /   -   .     9         !  :   9              C            D      C   ;  D   E      +     F   
-�>+     G   ��>+     H   ��8>,     I   F   G   H   +     J   m�Y>+     K   �7?+     L   W͓=,     M   J   K   L   +     N   Vb�<+     O   v�=+     P   Bs?,     Q   N   O   P   ,  C   R   I   M   Q   ;  D   S      +     T   dO@+     U   a�Ŀ+     V   '@��,     W   T   U   V   +     X   !x�+     Y   p �?+     Z   �6*=,     [   X   Y   Z   +     \   ��c=+     ]   6�P�+     ^   �U�?,     _   \   ]   ^   ,  C   `   W   [   _   +     g       +     j      +     n      +     �     �?  �          +  �   �      +     �      �+     �   33�>+     �       +     �     �D+     �   �~*?  �   +     �   �>+     �      A,  9   �   �   �   �   �   +     �        �      �     �   �      �      �   ;  �   �      +  �   �       +  �   �   �     �                                      ;         +  �                �   +  �         	 h                             i  h     j      i  ;  j  k         m     9   ;  m  n       q  �      +     {  _p�0+     }     A;  j  �      +     �     ?   �     9      �     9   ;  �  �     ;  �  �     +     �  �I@+     �  ��?+     �  �
�?+     �  �I?+     �  |� ?+     �  ���>+     �  ��"?+     �  Evt?+     �  ���?+     �  ��?+     �  ��@+     �  ��A+     �  �IA+     �  �S{A+     �  T�-@+     �  �Z�>+     �  ���.+     �  �O
+     �    �+     �  ��D;+     �    @@+     �  fff?   �     -   ;  �  �     6               �     ;     g     ;     v     ;     y     ;  .        ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;  �  �     ;  �  �     ;     �     ;     �     ;     �     >  E   R   >  S   `   =  i  l  k  =  9   o  n  O  -   p  o  o         n  q  r  p  d  h  s  l  _  9   t  s  r     �   O     u  t  t            >  g  u  A     w  g  n   =     x  w  >  v  x  =     z  v  �     |  z  {  �     ~  |  }  >  y  ~  =  i  �  �  =     �  y  P  -   �  �  �  W  9   �  �  �  O  -   �  �  �         >    �  A     �    g   =     �  �  >  �  �  A     �    j   =     �  �  >  �  �  =     �  �  >  �  �  9     �     �  >  �  �  =     �  �  >  �  �  9     �  "   �  >  �  �  =     �  g  >  �  �  9     �     �  >  �  �  9     �     �  >  �  �  =     �  �  A     �  �  g   =     �  �  �     �  �  �  A     �  �  g   >  �  �  =     �  �  >  �  �  9     �     �  >  �  �  9     �     �  >  g  �  =     �  v  >  �  �  9     �  A   �  =     �  �       �     .   �   �  �  �     �  �  �  >  �  �  =     �  �  A     �  g  n   >  �  �  =     �  g  >  �  �  9     �     �  >  �  �  9     �     �  >  �  �  =     �  �  =     �  �  P     �  �  �  �  =     �  �  P     �  �  �  �       �     .   �  �  �  >  �  �  =     �  �  =     �  �  Q     �  �      Q     �  �     Q     �  �     P  9   �  �  �  �  �  P  9   �  �   �   �   �   P  9   �  �   �   �   �     9   �     +   �  �  �  >  �  �  =  9   �  �  O     �  �  �            >  �  �  =     �  �  >  �  �  >  �  �   9  9   �  >   �  �  �  >  �  �  =  9   �  �  >  �  �  =  9   �  �  >  �  �  �  8  6            	   7     
   �     =     a   
   =  C   b   E   �     c   a   b   �  c   8  6            	   7        �     ;     f      A     h      g   =     i   h   A     k      j   =     l   k   �     m   i   l   A     o      n   =     p   o   �     q   m   p   >  f   q   =     r      O  -   s   r   r          =     t   f   P  -   u   t   t   �  -   v   s   u   A     w      j   =     x   w   Q     y   v       Q     z   v      P     {   y   z   x   �  {   8  6            	   7        �     =     ~      =  C      S   �     �   ~      �  �   8  6            	   7        �     ;     �      ;     �      A     �      n   =     �   �   A     �      j   =     �   �   �     �   �   �   >  �   �   =     �   �   A     �      g   =     �   �   �     �   �   �   A     �   �   g   >  �   �   =     �   �   A     �      g   =     �   �   �     �   �   �   A     �      j   =     �   �   �     �   �   �   �     �   �   �   A     �   �   n   >  �   �   A     �      n   =     �   �   A     �   �   j   >  �   �   =     �   �   �  �   8  6               7        �     ;     �      =     �      �     �   �   �   �     �   �   j   �     �   �   �   >  �   �   =     �      =     �   �   �     �   �   �   |     �   �   �  �   8  6               7        �      =     �           �      .   �   �   �   �  �   8  6     "          7     !   �  #   =     �   !        �      1   �   �   �   �  �   8  6     (       $   7     %   7     &   7     '   �  )   ;     �      ;     �      =     �   %   =     �   &   �     �   �   �   >  �   �   =     �   �   �     �   �   �   >  �   �   =     �   '   =     �   &   �     �   �   �   =     �   �   �     �   �   �   �  �   8  6     +          7     *   �  ,   =     �   *        �         �   �  �   8  6  -   1       /   7  .   0   �  2   =  -   �   0     -   �         �   �  �   8  6     4          7     3   �  5   =     �   3   �  �   8  6     7          7     6   �  8   ;     �      =     �   6   >  �   �   9     �      �   �  �   8  6  9   >       :   7     ;   7     <   7     =   �  ?   ;     �      =     �   <   �  �   �   �   �   �  �       �  �   �   �   �  �   =     �   <   �     �   �   �   �     �   �   �        �         �   �   =     �   =   �     �   �   �   �     �   �   �   >  �   �   =     �   ;   =     �   �   Q     �   �       Q     �   �      Q     �   �      P  9   �   �   �   �   �   �  �   �  �   �  �   �  �     9   �   �  �   8  6     A          7     @   �  B   ;     �      ;     �      ;     �      ;          ;          ;     
     ;          ;          ;          ;          ;          ;         ;     "     ;     %     ;     &     ;     1     ;  .   5     ;  .   >     ;  .   L     ;  .   M     ;     P     ;     [     ;     b     A  �   �   �   �   �   =     �   �   p     �   �   >  �   �   =     �   @   >  �   �   9        +   �   >  �      A  �       �   �   =         >      9     	  7     >    	  A  �       �     =         >      9       7     >  
    =       
  >      =         >      =       �   >      9       (                   (     �   >      =         n  �       >      =  �       �  �         �  !      �       !  �     >  "  �   9     #  4   "  �  #  �  !  =  �   '    �  �   (  '  �   �  *      �  (  )  /  �  )  =  �   +    �  �   ,  +    A  �   -  �   �   ,  =     .  -  >  &  .  �  *  �  /  >  &  g   �  *  �  *  =     0  &  >  %  0  =  �   2    A  �   3  �   �   2  =     4  3  >  1  4  =     6  %  p     7  6  =     8  1  p     9  8  P  -   :  7  9  =     ;  �   P  -   <  ;  ;  �  -   =  :  <  >  5  =  =     ?    P  -   @  ?  ?  =     A  
  P  -   B  A  A  =  �   C    o     D  C  =  �   E    �  �   F  E    o     G  F  P  -   H  D  G  P  -   I  �   �   �  -   J  H  I    -   K     .   @  B  J  >  >  K  =  -   N  >  >  M  N  9  -   O  1   M  >  L  O  =     Q  @   A     R  L  g   =     S  R  �     T  Q  S  A     U  L  j   =     V  U  A     W  L  g   =     X  W  �     Y  V  X  �     Z  T  Y  >  P  Z  A     \  5  g   =     ]  \  A     ^  5  j   =     _  ^  =     `  P       a     .   ]  _  `  >  [  a  =     c  [  >  b  c  9     d  4   b  �  d  8  