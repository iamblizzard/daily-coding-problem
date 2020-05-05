// We'll use Merkle Tree to dectect any change and synchronize it.
// Assume the files are stored in fixed-sized blocks on disk

#include <bits/stdc++.h>
// compile using -lcrypto flag
#include <openssl/sha.h>
using namespace std;

struct MerkleTree {
    string value;
    MerkleTree *left, *right;
    MerkleTree(string x, MerkleTree* l, MerkleTree* r) : value(x), left(l), right(r) {}
};
MerkleTree* buildMerkelTree(queue<MerkleTree*> q) {
    while(q.size() > 1) {
        MerkleTree *left = q.front();
        q.pop();
        MerkleTree *right = NULL;
        if(q.size() > 0) {
            right = q.front();
            q.pop();
        }
        //SHA_DIGEST_LENGTH := 20
        unsigned char hash[SHA_DIGEST_LENGTH];
        const unsigned char* str = (unsigned char*)left->value.c_str();
        SHA1(str, sizeof(str) - 1, hash);
        string value((char*) hash);
        if(right != NULL) {
            unsigned char hash[SHA_DIGEST_LENGTH];
            const unsigned char* str = (unsigned char*)right->value.c_str();
            SHA1(str, sizeof(str) - 1, hash);
            string temp((char*) hash);
            value += temp;
        }
        q.push(new MerkleTree(value, left, right));
    }
    return q.front();
}
MerkleTree* sync(MerkleTree* refNode, MerkleTree* mainNode) {
    if(refNode == NULL) {
        cout << "Change Detected: Data Item added in filesystem2\n";
        return mainNode;
    }
    if(mainNode == NULL) {
        cout << "Change Detected: Data Item deleted in filesystem2\n";
        return mainNode;
    }
    if(refNode->value == mainNode->value) {
        return refNode;
    }
    refNode->left  = sync(refNode->left,  mainNode->left);
    refNode->right = sync(refNode->right, mainNode->right);
    refNode->value = mainNode->value;
    return refNode;
}
void checkData(MerkleTree* node) {
    if(node == NULL) return;
    if(node->left == NULL && node->right == NULL) {
        cout << node->value << " ";
        return;
    }
    checkData(node->left);
    checkData(node->right);
}
int main()
{
    int n;
    cout << "Enter no. of blocks in filesystem 1: ";
    cin >> n;
    queue<MerkleTree*> q;
    string block;
    cout << "Enter blocks in filesysytem 1:\n";
    while(n--) {
        cin >> block;
        q.push(new MerkleTree(block, NULL, NULL));
    }
    MerkleTree* fs1Root = buildMerkelTree(q);

    cout << "Enter no. of blocks in filesystem 2: ";
    cin >> n;
    cout << "Enter blocks in filesystem 2:\n";
    queue<MerkleTree*>().swap(q);
    for(int i=0; i<n; ++i) {
        cin >> block;
        q.push(new MerkleTree(block, NULL, NULL));
    }
    MerkleTree* fs2Root = buildMerkelTree(q);

    checkData(fs1Root);
    cout << endl;
    // synchronize fs1 with fs2
    fs1Root = sync(fs1Root, fs2Root);
    checkData(fs1Root);
    cout << endl;
    return 0;
}