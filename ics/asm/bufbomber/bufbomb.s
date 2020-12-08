
bufbomb:     file format elf32-i386


Disassembly of section .init:

08048388 <_init>:
 8048388:	55                   	push   %ebp
 8048389:	89 e5                	mov    %esp,%ebp
 804838b:	53                   	push   %ebx
 804838c:	83 ec 04             	sub    $0x4,%esp
 804838f:	e8 00 00 00 00       	call   8048394 <_init+0xc>
 8048394:	5b                   	pop    %ebx
 8048395:	81 c3 60 1c 00 00    	add    $0x1c60,%ebx
 804839b:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 80483a1:	85 d2                	test   %edx,%edx
 80483a3:	74 05                	je     80483aa <_init+0x22>
 80483a5:	e8 1e 00 00 00       	call   80483c8 <__gmon_start__@plt>
 80483aa:	e8 01 01 00 00       	call   80484b0 <frame_dummy>
 80483af:	e8 bc 02 00 00       	call   8048670 <__do_global_ctors_aux>
 80483b4:	58                   	pop    %eax
 80483b5:	5b                   	pop    %ebx
 80483b6:	c9                   	leave  
 80483b7:	c3                   	ret    

Disassembly of section .plt:

080483b8 <__gmon_start__@plt-0x10>:
 80483b8:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 80483be:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 80483c4:	00 00                	add    %al,(%eax)
	...

080483c8 <__gmon_start__@plt>:
 80483c8:	ff 25 00 a0 04 08    	jmp    *0x804a000
 80483ce:	68 00 00 00 00       	push   $0x0
 80483d3:	e9 e0 ff ff ff       	jmp    80483b8 <_init+0x30>

080483d8 <__libc_start_main@plt>:
 80483d8:	ff 25 04 a0 04 08    	jmp    *0x804a004
 80483de:	68 08 00 00 00       	push   $0x8
 80483e3:	e9 d0 ff ff ff       	jmp    80483b8 <_init+0x30>

080483e8 <_IO_getc@plt>:
 80483e8:	ff 25 08 a0 04 08    	jmp    *0x804a008
 80483ee:	68 10 00 00 00       	push   $0x10
 80483f3:	e9 c0 ff ff ff       	jmp    80483b8 <_init+0x30>

080483f8 <__ctype_b_loc@plt>:
 80483f8:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 80483fe:	68 18 00 00 00       	push   $0x18
 8048403:	e9 b0 ff ff ff       	jmp    80483b8 <_init+0x30>

08048408 <printf@plt>:
 8048408:	ff 25 10 a0 04 08    	jmp    *0x804a010
 804840e:	68 20 00 00 00       	push   $0x20
 8048413:	e9 a0 ff ff ff       	jmp    80483b8 <_init+0x30>

Disassembly of section .text:

08048420 <_start>:
 8048420:	31 ed                	xor    %ebp,%ebp
 8048422:	5e                   	pop    %esi
 8048423:	89 e1                	mov    %esp,%ecx
 8048425:	83 e4 f0             	and    $0xfffffff0,%esp
 8048428:	50                   	push   %eax
 8048429:	54                   	push   %esp
 804842a:	52                   	push   %edx
 804842b:	68 00 86 04 08       	push   $0x8048600
 8048430:	68 10 86 04 08       	push   $0x8048610
 8048435:	51                   	push   %ecx
 8048436:	56                   	push   %esi
 8048437:	68 c0 85 04 08       	push   $0x80485c0
 804843c:	e8 97 ff ff ff       	call   80483d8 <__libc_start_main@plt>
 8048441:	f4                   	hlt    
 8048442:	90                   	nop    
 8048443:	90                   	nop    
 8048444:	90                   	nop    
 8048445:	90                   	nop    
 8048446:	90                   	nop    
 8048447:	90                   	nop    
 8048448:	90                   	nop    
 8048449:	90                   	nop    
 804844a:	90                   	nop    
 804844b:	90                   	nop    
 804844c:	90                   	nop    
 804844d:	90                   	nop    
 804844e:	90                   	nop    
 804844f:	90                   	nop    

08048450 <__do_global_dtors_aux>:
 8048450:	55                   	push   %ebp
 8048451:	89 e5                	mov    %esp,%ebp
 8048453:	53                   	push   %ebx
 8048454:	83 ec 04             	sub    $0x4,%esp
 8048457:	80 3d 20 a0 04 08 00 	cmpb   $0x0,0x804a020
 804845e:	75 40                	jne    80484a0 <__do_global_dtors_aux+0x50>
 8048460:	8b 15 24 a0 04 08    	mov    0x804a024,%edx
 8048466:	b8 18 9f 04 08       	mov    $0x8049f18,%eax
 804846b:	2d 14 9f 04 08       	sub    $0x8049f14,%eax
 8048470:	c1 f8 02             	sar    $0x2,%eax
 8048473:	8d 58 ff             	lea    -0x1(%eax),%ebx
 8048476:	39 da                	cmp    %ebx,%edx
 8048478:	73 1f                	jae    8048499 <__do_global_dtors_aux+0x49>
 804847a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048480:	8d 42 01             	lea    0x1(%edx),%eax
 8048483:	a3 24 a0 04 08       	mov    %eax,0x804a024
 8048488:	ff 14 85 14 9f 04 08 	call   *0x8049f14(,%eax,4)
 804848f:	8b 15 24 a0 04 08    	mov    0x804a024,%edx
 8048495:	39 da                	cmp    %ebx,%edx
 8048497:	72 e7                	jb     8048480 <__do_global_dtors_aux+0x30>
 8048499:	c6 05 20 a0 04 08 01 	movb   $0x1,0x804a020
 80484a0:	83 c4 04             	add    $0x4,%esp
 80484a3:	5b                   	pop    %ebx
 80484a4:	5d                   	pop    %ebp
 80484a5:	c3                   	ret    
 80484a6:	8d 76 00             	lea    0x0(%esi),%esi
 80484a9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080484b0 <frame_dummy>:
 80484b0:	55                   	push   %ebp
 80484b1:	89 e5                	mov    %esp,%ebp
 80484b3:	83 ec 08             	sub    $0x8,%esp
 80484b6:	a1 1c 9f 04 08       	mov    0x8049f1c,%eax
 80484bb:	85 c0                	test   %eax,%eax
 80484bd:	74 12                	je     80484d1 <frame_dummy+0x21>
 80484bf:	b8 00 00 00 00       	mov    $0x0,%eax
 80484c4:	85 c0                	test   %eax,%eax
 80484c6:	74 09                	je     80484d1 <frame_dummy+0x21>
 80484c8:	c7 04 24 1c 9f 04 08 	movl   $0x8049f1c,(%esp)
 80484cf:	ff d0                	call   *%eax
 80484d1:	c9                   	leave  
 80484d2:	c3                   	ret    
 80484d3:	90                   	nop    
 80484d4:	90                   	nop    
 80484d5:	90                   	nop    
 80484d6:	90                   	nop    
 80484d7:	90                   	nop    
 80484d8:	90                   	nop    
 80484d9:	90                   	nop    
 80484da:	90                   	nop    
 80484db:	90                   	nop    
 80484dc:	90                   	nop    
 80484dd:	90                   	nop    
 80484de:	90                   	nop    
 80484df:	90                   	nop    

080484e0 <getxs>:
 80484e0:	55                   	push   %ebp
 80484e1:	89 e5                	mov    %esp,%ebp
 80484e3:	57                   	push   %edi
 80484e4:	56                   	push   %esi
 80484e5:	53                   	push   %ebx
 80484e6:	83 ec 0c             	sub    $0xc,%esp
 80484e9:	8b 7d 08             	mov    0x8(%ebp),%edi
 80484ec:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 80484f3:	be 01 00 00 00       	mov    $0x1,%esi
 80484f8:	a1 1c a0 04 08       	mov    0x804a01c,%eax
 80484fd:	89 04 24             	mov    %eax,(%esp)
 8048500:	e8 e3 fe ff ff       	call   80483e8 <_IO_getc@plt>
 8048505:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048508:	89 c3                	mov    %eax,%ebx
 804850a:	74 44                	je     8048550 <getxs+0x70>
 804850c:	83 f8 0a             	cmp    $0xa,%eax
 804850f:	74 3f                	je     8048550 <getxs+0x70>
 8048511:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 8048518:	e8 db fe ff ff       	call   80483f8 <__ctype_b_loc@plt>
 804851d:	8b 00                	mov    (%eax),%eax
 804851f:	f6 44 58 01 10       	testb  $0x10,0x1(%eax,%ebx,2)
 8048524:	74 d2                	je     80484f8 <getxs+0x18>
 8048526:	8d 43 d0             	lea    -0x30(%ebx),%eax
 8048529:	83 f8 09             	cmp    $0x9,%eax
 804852c:	89 c2                	mov    %eax,%edx
 804852e:	76 0e                	jbe    804853e <getxs+0x5e>
 8048530:	8d 43 bf             	lea    -0x41(%ebx),%eax
 8048533:	83 f8 05             	cmp    $0x5,%eax
 8048536:	8d 53 c9             	lea    -0x37(%ebx),%edx
 8048539:	76 03                	jbe    804853e <getxs+0x5e>
 804853b:	8d 53 a9             	lea    -0x57(%ebx),%edx
 804853e:	85 f6                	test   %esi,%esi
 8048540:	74 1e                	je     8048560 <getxs+0x80>
 8048542:	31 f6                	xor    %esi,%esi
 8048544:	89 55 f0             	mov    %edx,-0x10(%ebp)
 8048547:	eb af                	jmp    80484f8 <getxs+0x18>
 8048549:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 8048550:	c6 07 00             	movb   $0x0,(%edi)
 8048553:	8b 45 08             	mov    0x8(%ebp),%eax
 8048556:	83 c4 0c             	add    $0xc,%esp
 8048559:	5b                   	pop    %ebx
 804855a:	5e                   	pop    %esi
 804855b:	5f                   	pop    %edi
 804855c:	5d                   	pop    %ebp
 804855d:	c3                   	ret    
 804855e:	66 90                	xchg   %ax,%ax
 8048560:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8048563:	c1 e0 04             	shl    $0x4,%eax
 8048566:	01 d0                	add    %edx,%eax
 8048568:	88 07                	mov    %al,(%edi)
 804856a:	83 c7 01             	add    $0x1,%edi
 804856d:	eb 84                	jmp    80484f3 <getxs+0x13>
 804856f:	90                   	nop    

08048570 <getbuf>:
 8048570:	55                   	push   %ebp
 8048571:	89 e5                	mov    %esp,%ebp
 8048573:	83 ec 18             	sub    $0x18,%esp
 8048576:	8d 45 f4             	lea    -0xc(%ebp),%eax
 8048579:	89 04 24             	mov    %eax,(%esp)
 804857c:	e8 5f ff ff ff       	call   80484e0 <getxs>
 8048581:	b8 01 00 00 00       	mov    $0x1,%eax
 8048586:	c9                   	leave  
 8048587:	c3                   	ret    
 8048588:	90                   	nop    
 8048589:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

08048590 <test>:
 8048590:	55                   	push   %ebp
 8048591:	89 e5                	mov    %esp,%ebp
 8048593:	83 ec 08             	sub    $0x8,%esp
 8048596:	c7 04 24 c0 86 04 08 	movl   $0x80486c0,(%esp)
 804859d:	e8 66 fe ff ff       	call   8048408 <printf@plt>
 80485a2:	e8 c9 ff ff ff       	call   8048570 <getbuf>
 80485a7:	c7 04 24 d1 86 04 08 	movl   $0x80486d1,(%esp)
 80485ae:	89 44 24 04          	mov    %eax,0x4(%esp)
 80485b2:	e8 51 fe ff ff       	call   8048408 <printf@plt>
 80485b7:	c9                   	leave  
 80485b8:	c3                   	ret    
 80485b9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

080485c0 <main>:
 80485c0:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 80485c4:	83 e4 f0             	and    $0xfffffff0,%esp
 80485c7:	ff 71 fc             	pushl  -0x4(%ecx)
 80485ca:	55                   	push   %ebp
 80485cb:	89 e5                	mov    %esp,%ebp
 80485cd:	8d 45 bc             	lea    -0x44(%ebp),%eax
 80485d0:	25 ff 0f 00 00       	and    $0xfff,%eax
 80485d5:	51                   	push   %ecx
 80485d6:	83 c0 1e             	add    $0x1e,%eax
 80485d9:	83 ec 44             	sub    $0x44,%esp
 80485dc:	25 f0 1f 00 00       	and    $0x1ff0,%eax
 80485e1:	29 c4                	sub    %eax,%esp
 80485e3:	8d 44 24 0f          	lea    0xf(%esp),%eax
 80485e7:	83 e0 f0             	and    $0xfffffff0,%eax
 80485ea:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
 80485f0:	e8 9b ff ff ff       	call   8048590 <test>
 80485f5:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 80485f8:	31 c0                	xor    %eax,%eax
 80485fa:	c9                   	leave  
 80485fb:	8d 61 fc             	lea    -0x4(%ecx),%esp
 80485fe:	c3                   	ret    
 80485ff:	90                   	nop    

08048600 <__libc_csu_fini>:
 8048600:	55                   	push   %ebp
 8048601:	89 e5                	mov    %esp,%ebp
 8048603:	5d                   	pop    %ebp
 8048604:	c3                   	ret    
 8048605:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048609:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048610 <__libc_csu_init>:
 8048610:	55                   	push   %ebp
 8048611:	89 e5                	mov    %esp,%ebp
 8048613:	57                   	push   %edi
 8048614:	56                   	push   %esi
 8048615:	53                   	push   %ebx
 8048616:	e8 4f 00 00 00       	call   804866a <__i686.get_pc_thunk.bx>
 804861b:	81 c3 d9 19 00 00    	add    $0x19d9,%ebx
 8048621:	83 ec 0c             	sub    $0xc,%esp
 8048624:	e8 5f fd ff ff       	call   8048388 <_init>
 8048629:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 804862f:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 8048635:	29 c7                	sub    %eax,%edi
 8048637:	c1 ff 02             	sar    $0x2,%edi
 804863a:	85 ff                	test   %edi,%edi
 804863c:	74 24                	je     8048662 <__libc_csu_init+0x52>
 804863e:	31 f6                	xor    %esi,%esi
 8048640:	8b 45 10             	mov    0x10(%ebp),%eax
 8048643:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048647:	8b 45 0c             	mov    0xc(%ebp),%eax
 804864a:	89 44 24 04          	mov    %eax,0x4(%esp)
 804864e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048651:	89 04 24             	mov    %eax,(%esp)
 8048654:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 804865b:	83 c6 01             	add    $0x1,%esi
 804865e:	39 fe                	cmp    %edi,%esi
 8048660:	72 de                	jb     8048640 <__libc_csu_init+0x30>
 8048662:	83 c4 0c             	add    $0xc,%esp
 8048665:	5b                   	pop    %ebx
 8048666:	5e                   	pop    %esi
 8048667:	5f                   	pop    %edi
 8048668:	5d                   	pop    %ebp
 8048669:	c3                   	ret    

0804866a <__i686.get_pc_thunk.bx>:
 804866a:	8b 1c 24             	mov    (%esp),%ebx
 804866d:	c3                   	ret    
 804866e:	90                   	nop    
 804866f:	90                   	nop    

08048670 <__do_global_ctors_aux>:
 8048670:	55                   	push   %ebp
 8048671:	89 e5                	mov    %esp,%ebp
 8048673:	53                   	push   %ebx
 8048674:	83 ec 04             	sub    $0x4,%esp
 8048677:	a1 0c 9f 04 08       	mov    0x8049f0c,%eax
 804867c:	83 f8 ff             	cmp    $0xffffffff,%eax
 804867f:	74 13                	je     8048694 <__do_global_ctors_aux+0x24>
 8048681:	bb 0c 9f 04 08       	mov    $0x8049f0c,%ebx
 8048686:	66 90                	xchg   %ax,%ax
 8048688:	83 eb 04             	sub    $0x4,%ebx
 804868b:	ff d0                	call   *%eax
 804868d:	8b 03                	mov    (%ebx),%eax
 804868f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048692:	75 f4                	jne    8048688 <__do_global_ctors_aux+0x18>
 8048694:	83 c4 04             	add    $0x4,%esp
 8048697:	5b                   	pop    %ebx
 8048698:	5d                   	pop    %ebp
 8048699:	c3                   	ret    
 804869a:	90                   	nop    
 804869b:	90                   	nop    

Disassembly of section .fini:

0804869c <_fini>:
 804869c:	55                   	push   %ebp
 804869d:	89 e5                	mov    %esp,%ebp
 804869f:	53                   	push   %ebx
 80486a0:	83 ec 04             	sub    $0x4,%esp
 80486a3:	e8 00 00 00 00       	call   80486a8 <_fini+0xc>
 80486a8:	5b                   	pop    %ebx
 80486a9:	81 c3 4c 19 00 00    	add    $0x194c,%ebx
 80486af:	e8 9c fd ff ff       	call   8048450 <__do_global_dtors_aux>
 80486b4:	59                   	pop    %ecx
 80486b5:	5b                   	pop    %ebx
 80486b6:	c9                   	leave  
 80486b7:	c3                   	ret    
