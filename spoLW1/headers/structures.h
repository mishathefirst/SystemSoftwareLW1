#ifndef LAB1SPO_STRUCTURES_H
#define LAB1SPO_STRUCTURES_H
#include "linux/types.h"
#include <stdint.h>
struct ext_dir {

    __le32 inode;
    __le16 rec_len;
    __u8 name_len;
    __u8 file_type;
    char name[255];
};

struct ext_group_desc{
    __u32  bg_block_bitmap;
    __u32  bg_inode_bitmap;
    __u32  bg_inode_table;
    __u16  bg_free_blocks_count;
    __u16  bg_free_inodes_count;
    __u16  bg_used_dirs_count;
    __u16  bg_pad;
    __u32  bg_reserved[3];
};

struct ext_inode {
    __le16 i_mode;
    __le16 i_uid;
    __le32 i_size;
    __le32 i_atime;
    __le32 i_ctime;
    __le32 i_mtime;
    __le32 i_dtime;
    __le16 i_gid;
    __le16 i_links_count;
    __le32 i_blocks;
    __le32 i_flags;
    union {
        struct {
            __le32 l_i_reserved1;
        } linux1;
        struct {
            __le32 h_i_translator;
        } hurd1;
        struct {
            __le32 m_i_reserved1;
        } masix1;
    } osd1;
    __le32 i_block[15];
    __le32 i_generation;
    __le32 i_file_acl;
    __le32 i_dir_acl;
    __le32 i_faddr;
    union {
        struct {
            __u8 l_i_frag;
            __u8 l_i_fsize;
            __u16 i_pad1;
            __le16 l_i_uid_high;
            __le16 l_i_gid_high;
            __u32 l_i_reserved2;
        } linux2;
        struct {
            __u8 h_i_frag;
            __u8 h_i_fsize;
            __le16 h_i_mode_high;
            __le16 h_i_uid_high;
            __le16 h_i_gid_high;
            __le32 h_i_author;
        } hurd2;
        struct {
            __u8 m_i_frag;
            __u8 m_i_fsize;
            __u16 m_pad1;
            __u32 m_i_reserved2[2];
        } masix2;
    } osd2;
};

struct ext_super_block {
    __u32 s_inodes_count;
    __u32 s_blocks_count;
    __u32 s_r_blocks_count;
    __u32 s_free_blocks_count;
    __u32 s_free_inodes_count;
    __u32 s_first_data_block;
    __u32 s_log_block_size;
    __s32 s_log_frag_size;
    __u32 s_blocks_per_group;
    __u32 s_frags_per_group;
    __u32 s_inodes_per_group;
    __u32 s_mtime;
    __u32 s_wtime;
    __u16 s_mnt_count;
    __s16 s_max_mnt_count;
    __u16 s_magic;
    __u16 s_state;
    __u16 s_errors;
    __u16 s_minor_rev_level;
    __u32 s_lastcheck;
    __u32 s_checkinterval;
    __u32 s_creator_os;
    __u32 s_rev_level;
    __u16 s_def_resuid;
    __u16 s_def_resgid;
    __u32 s_first_ino;
    __u16 s_inode_size;
    __u16 s_block_group_nr;
    __u32 s_feature_compat;
    __u32 s_feature_incompat;
    __u32 s_feature_ro_compat;
    __u8 s_uuid[16];
    char s_volume_name[16];
    char s_last_mounted[64];
    __u32 s_algorithm_usage_bitmap;
    __u8 s_journal_uuid[16];
    __u32 s_journal_inum;
    __u32 s_journal_dev;
    __u32 s_last_orphan;
    __u32 s_hash_seed[4];
    __u8 s_def_hash_version;
    __u8 s_reserved_char_pad;
    __u16 s_reserved_word_pad;
    __u32 s_default_mount_opts;
    __u32 s_first_meta_bg;
    __u32 s_reserved[190];
};



#endif //LAB1SPO_STRUCTURES_H
