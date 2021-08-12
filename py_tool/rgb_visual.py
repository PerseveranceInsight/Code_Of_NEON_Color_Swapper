import numpy as np
import cv2 as cv

if __name__ == '__main__':
    ori_img = cv.imread('../data/icon_test.png')
    r_img = ori_img[:, :, 0]
    g_img = ori_img[:, :, 1]
    b_img = ori_img[:, :, 2]
    ori_img_flatten = ori_img.flatten(order='C')
    r_img_flatten = r_img.flatten(order='C')
    g_img_flatten = g_img.flatten(order='C')
    b_img_flatten = b_img.flatten(order='C')
    r_sample = ori_img_flatten[0::3]
    g_sample = ori_img_flatten[1::3]
    b_sample = ori_img_flatten[2::3]
    print('r : {0}'.format(np.where(r_img_flatten != r_sample)))
    print('g : {0}'.format(np.where(g_img_flatten != g_sample)))
    print('b : {0}'.format(np.where(b_img_flatten != b_sample)))
    img_interleve_file = open('../data/icon_interleve_npy.bin', 'wb')
    np.save(img_interleve_file, ori_img_flatten)
    img_interleve = np.load('../data/icon_interleve_npy.bin')
    img_interleve.astype('uint8').tofile('../data/icon_interleve.bin')
