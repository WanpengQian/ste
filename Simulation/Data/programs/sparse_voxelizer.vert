 ފ          #     <             K  
 	 SPV_KHR_shader_draw_parameters       GLSL.std.450                      main    �   �         *       �   	 GL_ARB_shader_draw_parameters    
 GL_GOOGLE_cpp_style_line_directive       main      
   mesh_descriptor  	 
       model_transform_matrix   	 
      tangent_transform_quat    
      bounding_sphere   
      material_id   
      light_caster      
      _unused0      
      _unused1         transform_model(struct-mesh_descriptor-mf34-vf4-vf4-i1-i1-f1-f11;vf3;        mesh         v        quat_mul_quat(vf4;vf4;       q1       q2       extract_tangent_bitangent_from_tangent_frame(vf4;        q    
 "   extract_tangent_frame(vf4;vf4;        world_transform   !   tangent_frame     1   q     �   q     �   param     �   param     �   bt    �   param     �   draw_id   �   gl_BaseInstanceARB    �   md    �   mesh_descriptor  	 �       model_transform_matrix   	 �      tangent_transform_quat    �      bounding_sphere   �      material_id   �      light_caster      �      _unused0      �      _unused1     	 �   mesh_descriptors_binding     	 �       mesh_descriptor_buffer    �         �   wpos      �   vert      �   param     �   param     �   tangent_frame_transform      dual_quaternion          real            dual     
   view_transform_buffer_struct            view_transform   	      inverse_view_transform         eye_position     
   view_transform_buffer_binding    	       view_transform_buffer               param     	  param       tbn     tangent_frame_quat      param       param       scene_transform         frag_normal        frag_texcoords         material_id     vout        tex_coords    (  gl_PerVertex      (      gl_Position   (     gl_PointSize      (     gl_ClipDistance   (     gl_CullDistance   *        2  mesh_draw_params      2      count     2     first_index   2     vertex_offset    	 4  mesh_draw_params_binding     	 4      mesh_draw_params_buffer   6       
 8  proj_transform_buffer_struct      8      proj_xywz     8     backbuffer_size   8     tan_half_fovy     8     aspect   
 9  proj_transform_buffer_binding    	 9      proj_transform_buffer     ;      G  �      I  H  �          H  �       #       H  �             H  �      #   0   H  �      #   @   H  �      #   P   H  �      #   T   H  �      #   X   H  �      #   \   G  �      `   H  �          H  �          H  �       #       G  �      G  �   "      G  �   !      G  �         H         #       H        #      H        #       H       #       H       #   @   H        #       G       G    "      G    !       G           H          G       G           G          H  (             H  (           H  (           H  (           G  (     H  2      #       H  2     #      H  2     #      G  3        H  4         H  4         H  4      #       G  4     G  6  "      G  6  !      H  8      #       H  8     #      H  8     #      H  8     #      H  9      #       G  9     G  ;  "      G  ;  !           !                                         	           	 
            	   	                  
                          !                          !                         !                      !              +     %     �?+  	   *          +           2           +  2   3         4         +     W      @+  2   X      +  2   ^      +  2   g       +     �          �         +  	   �         �      2      �      	   ;  �   �       	 �            	   	           �   �     �   �      �      �   ;  �   �         �      �   +  	   �      +  	   �         �      	   +  	   �      +  	   �      +  	   �         �         ;  �   �                                              ;                                          ;                            	             ;                   ;                      !           %     	     '     X     (        '  '     )     (  ;  )  *        0          2  2   2   	     3  2    4  3     5     4  ;  5  6       7  2        8     7          9  8     :     9  ;  :  ;     6               �     ;  �   �      ;     �      ;     �      ;     �      ;     �      ;     �      ;          ;     	     ;         ;          ;          =  	   �   �   |  2   �   �   >  �   �   =  2   �   �   A  �   �   �   *   �   =  �   �   �   Q     �   �       A  +   �   �   *   >  �   �   Q     �   �      A     �   �   �   >  �   �   Q     �   �      A     �   �   �   >  �   �   Q  	   �   �      A  �   �   �   �   >  �   �   Q  	   �   �      A  �   �   �   �   >  �   �   Q     �   �      A  4   �   �   �   >  �   �   Q     �   �      A  4   �   �   �   >  �   �   =  
   �   �   >  �   �   =     �   �   >  �   �   9     �      �   �   >  �   �   A        *   *   *   =         >      A     
  �   �   =       
  >  	    9            	  >  �     =       �   >      =         >      9       "       >      =        A        �   >      A         �   =          A  !  "    *   >  "     A  �   #  �   �   =  	   $  #  A  %  &    �   >  &  $  =     +  �   Q     ,  +      Q     -  +     Q     .  +     P     /  ,  -  .  %   A  0  1  *  *   >  1  /  �  8  6               7        7        �     =     $      Q     &   $       Q     '   $      Q     (   $      P     )   &   '   (   %   A  +   ,      *   =     -   ,   �     .   )   -   �  .   8  6               7        7        �     ;     1      A  4   5      3   =     6   5   A  4   7      3   =     8   7   �     9   6   8   =     :      O     ;   :   :             =     <      O     =   <   <             �     >   ;   =   �     ?   9   >   A  4   @   1   3   >  @   ?   A  4   A      3   =     B   A   =     C      O     D   C   C             �     E   D   B   A  4   F      3   =     G   F   =     H      O     I   H   H             �     J   I   G   �     K   E   J   =     L      O     M   L   L             =     N      O     O   N   N                  P      D   M   O   �     Q   K   P   =     R   1   O 	    S   R   Q               >  1   S   =     T   1   �  T   8  6               7        �     A  4   Y      X   =     Z   Y   A  4   [      X   =     \   [   �     ]   Z   \   A  4   _      ^   =     `   _   A  4   a      ^   =     b   a   �     c   `   b   �     d   ]   c   �     e   W   d   �     f   %   e   A  4   h      g   =     i   h   A  4   j      X   =     k   j   �     l   i   k   A  4   m      3   =     n   m   A  4   o      ^   =     p   o   �     q   n   p   �     r   l   q   �     s   W   r   A  4   t      g   =     u   t   A  4   v      ^   =     w   v   �     x   u   w   A  4   y      3   =     z   y   A  4   {      X   =     |   {   �     }   z   |   �     ~   x   }   �        W   ~   A  4   �      g   =     �   �   A  4   �      X   =     �   �   �     �   �   �   A  4   �      3   =     �   �   A  4   �      ^   =     �   �   �     �   �   �   �     �   �   �   �     �   W   �   A  4   �      g   =     �   �   A  4   �      g   =     �   �   �     �   �   �   A  4   �      ^   =     �   �   A  4   �      ^   =     �   �   �     �   �   �   �     �   �   �   �     �   W   �   �     �   %   �   A  4   �      X   =     �   �   A  4   �      ^   =     �   �   �     �   �   �   A  4   �      3   =     �   �   A  4   �      g   =     �   �   �     �   �   �   �     �   �   �   �     �   W   �   P     �   f   s      P     �   �   �   �   P     �   �   �   �  �   8  6     "          7         7     !   �  #   ;     �      ;     �      ;     �      ;  �   �      ;     �      =     �       >  �   �   =     �   !   >  �   �   9     �      �   �   >  �   �   =     �   �   >  �   �   9     �      �   >  �   �   A     �   �   �   =     �   �   A     �   �   *   =     �   �   A     �   �   *   =     �   �   A     �   �   �   =     �   �        �      D   �   �   A  4   �   !   3   =     �   �        �         �   �     �   �   �   Q     �   �       Q     �   �      Q     �   �      Q     �   �       Q     �   �      Q     �   �      Q     �   �       Q     �   �      Q     �   �      P     �   �   �   �   P     �   �   �   �   P     �   �   �   �   P     �   �   �   �   �  �   8  