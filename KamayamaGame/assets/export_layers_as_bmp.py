GIMP 2.10.36 Python Console
Python 2.7.18 (default, Jul  1 2023, 20:56:56)  [GCC 13.1.0 64 bit (AMD64)]
>>> from gimpfu import *
>>> 
>>> def export_layers_as_bmp(image, drawable, output_path):
...     pdb.gimp_image_undo_group_start(image)
...     
...     # 各レイヤーの幅と高さを取得
...     layers = image.layers
...     layer_width = layers[0].width
...     layer_height = layers[0].height
...     
...     # 横一列のキャンバスサイズを計算
...     total_width = layer_width * len(layers)
...     total_height = layer_height
...     
...     # 新しい画像を作成
...     new_image = pdb.gimp_image_new(total_width, total_height, RGB)
...     new_layer = pdb.gimp_layer_new(new_image, total_width, total_height, RGB_IMAGE, "Merged Layer", 100, NORMAL_MODE)
...     pdb.gimp_image_add_layer(new_image, new_layer, 0)
...     
...     # 各レイヤーを新しい画像に横一列で配置
...     for i, layer in enumerate(layers):
...         # レイヤーをコピーして新しい画像に貼り付け
...         offset_x = i * layer_width
...         floating_sel = pdb.gimp_edit_copy(layer)
...         pasted_layer = pdb.gimp_edit_paste(new_layer, True)
...         pdb.gimp_layer_set_offsets(pasted_layer, offset_x, 0)
...         pdb.gimp_floating_sel_anchor(pasted_layer)
...     
...     # BMP形式でエクスポート
...     pdb.file_bmp_save(new_image, new_layer, output_path, output_path, 0)
...     pdb.gimp_image_delete(new_image)
...     pdb.gimp_image_undo_group_end(image)
... 
>>> register(
...     "python-fu-export-layers-as-bmp",
...     "Export all layers as a single row BMP image",
...     "Exports all layers in the current image as a single row BMP image",
...     "Your Name",
...     "Your Name",
...     "2024",
...     "<Image>/Filters/Custom/Export Layers as BMP",
...     "*",
...     [
...         (PF_FILE, "output_path", "Output BMP file", "")
...     ],
...     [],
...     export_layers_as_bmp)
>>> 
>>> main()