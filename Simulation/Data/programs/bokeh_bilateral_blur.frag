 ފ         #     2             2        GLSL.std.450                     main    r  z                 �   
 GL_GOOGLE_cpp_style_line_directive       main         max_element(vf2;      
   v        luminance(vf3;       color        _hash(u1;        x        _floatConstruct(u1;      m         fast_rand(f1;        x     '   project(vf4;vf4;      %   proj_xywz     &   v     ,   unproject_depth(f1;f1;    *   d     +   n     0   project(vf4;      /   v     4   project(vf3;      3   v     7   projection_near_clip(     9   projection_aspect(   	 ;   projection_tan_half_fovy(     >   unproject_depth(f1;   =   d     D   color(vf2;vf2;f1;     A   coords    B   blur      C   max_blur      I   coc(f1;f1;    G   s     H   focal    
 M   conversion_matrix_rgb_to_xyz     
 [   conversion_matrix_xyz_to_rgb      �   f     �   param     �   param    
 �   proj_transform_buffer_struct      �       proj_xywz     �      backbuffer_size   �      tan_half_fovy     �      aspect   
 �   proj_transform_buffer_binding    	 �       proj_transform_buffer     �         �   param     �   param     �   param     �   param     �   param     �   jitter    �   col   �   hdr     lum     param       thresh    !  f     "  aperture_t   	 "      aperture_focal_length     "     aperture_diameter     $        (  A     ,  s1    2  s2    >  C     G  projected     L  param     N  c     T  aperture_h    Z  aperture_w    ^  norm_coc      i  size      o  col   r  uv    v  d     w  depth_map     z  gl_FragCoord      �  z     �  param     �  focal     �  hdr_bokeh_parameters      �      lum_min   �     lum_max   �     focus    	 �  hdr_bokeh_parameters_buffer   �      params    �        �  coc_size      �  param     �  param     �  blur      �  blur_texels   �  max_blur      �  param     �  rings     �  noise     �  param     �  param     �  wh    �  s     �  i     �  ringsamples   �  j     �  angle     �  c     �  w     �  param     �  param     �  param       frag_color    '  dual_quaternion   '      real      '     dual     
 (  view_transform_buffer_struct      (      view_transform   	 (     inverse_view_transform    (     eye_position     
 )  view_transform_buffer_binding    	 )      view_transform_buffer     +        /  gbuffer   0  downsampled_depth_map     1  backface_depth_map  H  �       #       H  �      #      H  �      #      H  �      #      H  �       #       G  �      G  �   "      G  �   !      G  �   "       G  �   !       H  "      #       H  "     #      G  "     G  r         G  w  "      G  w  !      G  z        H  �      #       H  �     #      H  �     #      H  �         H  �         H  �      #       G  �     G  �  "       G  �  !      G           H  '      #       H  '     #      H  (      #       H  (     #       H  (     #   @   H  )      #       G  )     G  +  "      G  +  !       G  /  "      G  /  !      G  0  "      G  0  !      G  1  "      G  1  !           !                                        !  	                                !                                    !           !                       !             "            #      "   !  $   "   #   #   !  )            !  .   "   #   !  2   "      !  6      !  @               !  F              K            L      K   ;  L   M      +     N   
-�>+     O   ��>+     P   ��8>,     Q   N   O   P   +     R   m�Y>+     S   �7?+     T   W͓=,     U   R   S   T   +     V   Vb�<+     W   v�=+     X   Bs?,     Y   V   W   X   ,  K   Z   Q   U   Y   ;  L   [      +     \   dO@+     ]   a�Ŀ+     ^   '@��,     _   \   ]   ^   +     `   !x�+     a   p �?+     b   �6*=,     c   `   a   b   +     d   ��c=+     e   6�P�+     f   �U�?,     g   d   e   f   ,  K   h   _   c   g   +     i       +     l      +     w   
   +     |      +     �      +     �      +     �      +     �   �� +     �     �?+     �     �?  �           �   "   �           �   �      �      �   ;  �   �        �          +  �   �          �      "   +     �         �         +  �   �      +  �   �       	 �                              �   �      �       �   ;  �   �       +     �       ,     �   �   �   +     �   -�]�+     �      �,     �   �   �   +       -�]?,         �   +          ?+         �?,       �   �   �     "           #  	   "  ;  #  $  	      %  	      +  �   )     +     0  (knN  8  ,     <  �   �   +     U     @  l  �         q        ;  q  r     ;  �   w         y     "   ;  y  z       �             �  �     �     �  ;  �  �     +     �    �@   �     �   +     �     A+  �   �  
      �        +     �  ��8+  �   �     +     �  ��@           ;         +       �I@+       ��?+       �
�?+       �I?+       |� ?+       ���>+       ��"?+       Evt?+       ���?+       ��?+       ��A+       �IA+       �S{A+       T�-@+       �Z�>+       ���.+       �O
+          �+  �   !     +     "    �D+     #  _p�0+     $  ��D;+     %    @@+     &  fff?  '  "   "     (  '  '  "     )  (     *     )  ;  *  +      	 ,                            -  ,     .      -  ;  .  /      ;  �   0      ;  �   1      6               �     ;     i     ;     o     ;     v     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     ;  �  �     ;     �     ;     �     ;     �     ;     �     ;     �     ;  �  �     ;  �  �     ;  �  �     ;     �     ;     �     ;     �     ;     �     ;     �     ;     �     >  M   Z   >  [   h   =  �   j  �   d  �   k  j  g  l  m  k  �   o     n  m  >  i  n  =  �   p  �   =     s  r  W  "   t  p  s  O     u  t  t            >  o  u  =  �   x  w  =  "   {  z  O     |  {  {         n  l  }  |  d  �   ~  x  _  "     ~  }     �   Q     �        >  v  �  =     �  v  >  �  �  9     �  >   �  >  �  �  A  �   �  �  �   �   =     �  �  >  �  �  =     �  �  >  �  �  =     �  �  >  �  �  9     �  I   �  �  >  �  �  =     �  �  =     �  i  P     �  �  �  �     �  �  �       �     %   �  �  >  �  �  =     �  �  =     �  i  �     �  �  �  >  �  �  =     �  �  >  �  �  9     �     �  >  �  �  =     �  �  �     �  �  �  �     �  �  �       �        �  n  �   �  �    �   �     '   �  �  >  �  �  =  �   �  �  �  8  �  �  �   �  �      �  �  �  �  �  �  A  �  �  r  i   =     �  �  >  �  �  9     �      �  A  �  �  r  l   =     �  �  >  �  �  9     �      �  P     �  �  �  �     �  �  �  =     �  �  �     �  �  �  >  �  �  =     �  �  �     �  �  �   =     �  �  �     �  �  �  >  �  �  >  �  �   >  �  )  �  �  �  �  �  �  �      �  �  �  �  =  �   �  �  =  �   �  �  �  8  �  �  �  �  �  �  �  �  �  =  �   �  �  �  �   �  �  �  >  �  �  >  �  �   �  �  �  �  �  �  �      �  �  �  �  =  �   �  �  =  �   �  �  �  8  �  �  �  �  �  �  �  �  �  =  �   �  �  o     �  �  �     �  �  �  =  �   �  �  o     �  �  �     �  �  �  >  �  �  =     �  �       �        �  =     �  �       �        �  P     �  �  �  =  �   �  �  o     �  �  �     �  �  �  >  �  �  =  �   �  �  o     �  �  =  �   �  �  o     �  �  �     �  �  �       �     .   �   �    >  �  �  =     �  r  =     �  �  =     �  �  �     �  �  �  �     �  �  �  >  �  �  =     �  �  >  �  �  =     �  �  >  �  �  9     �  D   �  �  �  =     �  �  �     �  �  �  =     �  o  �        �  �  >  o     =       �  =       �  �           >  �    �  �  �  �  =  �     �  �  �       )  >  �    �  �  �  �  �  �  �  �  =  �     �  �  �       )  >  �    �  �  �  �  =       �  =     	  o  P     
        �       	  
  >  o    �  �  �  �  =       o  >      �  8  6            	   7     
   �     A     j   
   i   =     k   j   A     m   
   l   =     n   m        o      (   k   n   �  o   8  6               7        �     =     r      �     s   r   U   �  s   8  6               7        �     =     v      �     x   v   w   =     y      �     z   y   x   >     z   =     {      �     }   {   |   =     ~      �        ~   }   >        =     �      �     �   �   �   =     �      �     �   �   �   >     �   =     �      �     �   �   �   =     �      �     �   �   �   >     �   =     �      �     �   �   �   =     �      �     �   �   �   >     �   =     �      �  �   8  6               7        �     ;     �      =     �      �     �   �   �   >     �   =     �      �     �   �   �   >     �   =     �      |     �   �   >  �   �   =     �   �   �     �   �   �   �  �   8  6                7        �  !   ;     �      ;     �      =     �      |     �   �   >  �   �   9     �      �   >  �   �   9     �      �   �  �   8  6  "   '       $   7  #   %   7  #   &   �  (   =  "   �   &   O 	 "   �   �   �                =  "   �   %   �  "   �   �   �   �  �   8  6     ,       )   7     *   7     +   �  -   =     �   +        �   �   =     �   *   �     �   �   �   �  �   8  6  "   0       .   7  #   /   �  1   ;  #   �      ;  #   �      A  �   �   �   �   �   =  "   �   �   >  �   �   =  "   �   /   >  �   �   9  "   �   '   �   �   �  �   8  6  "   4       2   7     3   �  5   ;  #   �      =     �   3   Q     �   �       Q     �   �      Q     �   �      P  "   �   �   �   �   �   >  �   �   9  "   �   0   �   �  �   8  6     7       6   �  8   A  �   �   �   �   �   �   =     �   �   �  �   8  6     9       6   �  :   A  �   �   �   �   �   =     �   �   �  �   8  6     ;       6   �  <   A  �   �   �   �   �   =     �   �   �  �   8  6     >          7     =   �  ?   ;     �      ;     �      9     �   7   =     �   =   >  �   �   >  �   �   9     �   ,   �   �   �  �   8  6     D       @   7     A   7     B   7     C   �  E   ;     �      ;     �      ;          ;          ;          =     �   B   �     �   �   �   >  �   �   =  �   �   �   =     �   A   =     �   �   �     �   �   �   �     �   �   �   W  "   �   �   �   Q     �   �       A     �   �   i   >  �   �   =  �   �   �   =     �   A   =     �   �   �     �   �   �   �     �   �   �   W  "   �   �   �   Q     �   �      A        �   l   >     �   =  �     �   =       A   =       �   �           �           W  "         Q     	       A     
  �   �   >  
  	  =       �   >      9            >      =         �           �                     (     �   >      =       �   =       �   =         =       C   �           P                       .         �           �    8  6     I       F   7     G   7     H   �  J   ;     !     ;     (     ;     ,     ;     2     ;     >     ;  #   G     ;     L     ;     N     ;     T     ;     Z     ;     ^     A  %  &  $  �   =     '  &  >  !  '  A  %  *  $  )  =     +  *  >  (  +  =     -  H        .  -  =     /  !       1     +   .  /  0  >  ,  1  =     3  G        4  3       5     %   4  0  >  2  5  =     6  ,  =     7  2  �  8  9  6  7  �  ;      �  9  :  ;  �  :  �  <  �  ;  =     ?  (  =     @  ,  =     A  2  �     B  @  A       C        B  �     D  ?  C  =     E  2  �     F  D  E  >  >  F  =     H  >  =     I  ,       J  I  P     K  H  �   J  >  L  K  9  "   M  4   L  >  G  M  A     O  G  i   =     P  O  A     Q  G  �   =     R  Q  �     S  P  R  >  N  S  9     V  ;   �     W  U  V  9     X  7   �     Y  W  X  >  T  Y  =     [  T  9     \  9   �     ]  [  \  >  Z  ]  =     _  N  =     `  Z  =     a  T  P     b  `  a  P     c  _  _  �     d  c  b  >  ^  d  =     e  ^  �     f  e    �  f  8  